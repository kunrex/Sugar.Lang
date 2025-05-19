#include "compiler.h"

#include <fstream>
#include <sstream>
#include <filesystem>

#include "Exceptions/log_exception.h"
#include "Exceptions/exception_manager.h"
#include "Exceptions/Compilation/source_file_exception.h"

#include "Lexing/Lexer/lexer.h"

#include "Parsing/Parser/parser.h"

#include "Analysis/Structure/source_file.h"

#include "Analysis/Creation/Binding/local_binder.h"
#include "Analysis/Creation/Binding/global_binder.h"
#include "Analysis/Creation/Binding/project_binder.h"

#include "Analysis/Creation/Transpiling/cil_transpiler.h"

#include "Analysis/Structure/Wrappers/Value/short.h"
#include "Analysis/Structure/Wrappers/Value/integer.h"
#include "Analysis/Structure/Wrappers/Value/long.h"
#include "Analysis/Structure/Wrappers/Value/float.h"
#include "Analysis/Structure/Wrappers/Value/double.h"
#include "Analysis/Structure/Wrappers/Value/boolean.h"
#include "Analysis/Structure/Wrappers/Value/character.h"
#include "Analysis/Structure/Wrappers/Reference/string.h"

using namespace std;
namespace fs = std::filesystem;

using namespace Exceptions;

using namespace Lexing;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Statements;

using namespace Parsing;

using namespace Analysis::Creation;
using namespace Analysis::Creation::Binding;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

constexpr string_view source_extension = ".sugar";

void PushStructure(const std::string& strPath, SourceDirectory* const directory)
{
    const auto path = fs::path(strPath);

    if (!exists(path) || !is_directory(path))
    {
        ExceptionManager::Instance().AddChild(new SourceFileException(path));
        return;
    }

    for (const auto& entry : fs::directory_iterator(path))
    {
        const auto& childPath = entry.path();
        const auto name = childPath.filename().string();

        if (is_directory(entry))
        {
            const auto child = new SourceDirectory(name, false);

            directory->AddChild(name, child);
            PushStructure(childPath.string(), child);
        }
        else if (is_regular_file(entry) && childPath.extension() == source_extension)
        {
            std::ifstream file(childPath, std::ios::binary);
            if (!file)
            {
                ExceptionManager::Instance().AddChild(new SourceFileException(childPath));
                return;
            }

            const auto clippedName = name.substr(0, name.find_last_of('.'));
            directory->AddChild(clippedName, new SourceFile(clippedName, string((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>())));
        }
    }
}

Compiler::Compiler(const std::string& sourcePath) : sourcePath(sourcePath)
{
    const fs::path path = sourcePath;
    if (!exists(path) || !is_directory(path))
    {
        ExceptionManager::Instance().AddChild(new SourceFileException(path));
        return;
    }

    const auto name = path.filename().string();
    source = new SourceDirectory(name, true);

    ExceptionManager::Instance();
    PushStructure(sourcePath, source);
}

void Compiler::Compile() const
{
    if (ExceptionManager::Instance().ChildCount() > 0)
    {
        std::cout << "Failed to initialise source system." << std::endl;
        return;
    }

    Lexer::Instance();
    Parser::Instance();

    Short::Instance();
    Integer::Instance();
    Long::Instance();
    Float::Instance();
    Double::Instance();
    Boolean::Instance();
    Character::Instance();
    String::Instance();

    std::vector<void(SourceObject::*)()> steps;
    steps.push_back(&SourceObject::LexParse);
    steps.push_back(&SourceObject::InitDataTypes);
    steps.push_back(&SourceObject::ManageImports);
    steps.push_back(&SourceObject::BindGlobal);
    //steps.push_back(&SourceObject::BindLocal);

    try
    {
        for (const auto func: steps)
        {
            (source->*func)();

            if (ExceptionManager::Instance().LogAllExceptions())
            {
                delete source;
                return;
            }
        }

        source->Print("", true);;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    /*
    CILTranspiler transpiler(name, sourcePath, source);
    transpiler.Transpile();

    if (!ExceptionManager::Instance().LogAllExceptions())
        cout << "Compiled successfully at " << transpiler.OutputFile() << endl;
    */

    delete source;
}
