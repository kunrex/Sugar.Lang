#include "compiler.h"

#include <fstream>
#include <sstream>
#include <filesystem>

#include "Lexing/Lexer/lexer.h"
#include "Exceptions/exception_manager.h"
#include "Analysis/Structure/source_file.h"
#include "Exceptions/Compiling/source_file_exception.h"
#include "Parsing/Parser/parser.h"

using namespace std;
namespace fs = std::filesystem;

using namespace Exceptions;

using namespace Lexing;

using namespace Parsing;

using namespace Analysis::Structure;

constexpr std::string source_extension = ".sugar";

Compiler::Compiler(const std::string& sourcePath)
{
    const fs::path path = sourcePath;
    if (!exists(path) || !is_directory(path))
    {
        ExceptionManager::Instance().AddChild(new SourceFileException(path));
        return;
    }

    const auto name = path.filename().string();
    source = new SourceDirectory(name);

    ExceptionManager::Instance();
    PushDirectory(sourcePath, source);
}

void Compiler::PushDirectory(const std::string& strPath, SourceDirectory* const directory)
{
    const auto path = fs::path(strPath);

    if (!exists(path) || !is_directory(path)) {
        ExceptionManager::Instance().AddChild(new SourceFileException(path));
        return;
    }

    for (const auto& entry : fs::directory_iterator(path))
    {
        const auto& childPath = entry.path();
        const auto name = childPath.filename().string();

        if (is_directory(entry))
        {
            const auto child = new SourceDirectory(name);
            directory->AddChild(child);

            PushDirectory(childPath.string(), child);
        }
        else if (is_regular_file(entry) && childPath.extension() == source_extension)
        {
            std::ifstream file(childPath, std::ios::binary);
            if (!file)
            {
                ExceptionManager::Instance().AddChild(new SourceFileException(childPath));
                return;
            }

            directory->AddChild(new SourceFile(name, string((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>())));
        }
    }
}

void Compiler::Compile()
{
    if (ExceptionManager::Instance().ChildCount() > 0)
        return;

    Lexer::Instance();
    Parser::Instance();
    LexParse(source);

    if (ExceptionManager::Instance().ChildCount() > 0)
    {
        delete source;
        return;
    }

    //Analyse
    //Transpile
    //yayyy
}

void Compiler::LexParse(SourceObject* const directory)
{
    for (const auto child: *directory)
    {
        if (child->SourceType() == Enums::SourceType::Directory)
            LexParse(child);
        else
        {
            const auto casted = static_cast<SourceFile* const>(child);
            const auto previous = ExceptionManager::Instance().ChildCount();
            Lexer::Instance().Lex(casted);

            if (ExceptionManager::Instance().ChildCount() == previous)
                Parser::Instance().Parse(casted);
        }
    }
}









