#include "compiler.h"

#include <fstream>
#include <sstream>
#include <format>
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
#include "Analysis/Structure/Global/Functions/void_function.h"
#include "Analysis/Structure/Wrappers/Generic/array.h"

#include "Analysis/Structure/Wrappers/Value/short.h"
#include "Analysis/Structure/Wrappers/Value/integer.h"
#include "Analysis/Structure/Wrappers/Value/long.h"
#include "Analysis/Structure/Wrappers/Value/float.h"
#include "Analysis/Structure/Wrappers/Value/double.h"
#include "Analysis/Structure/Wrappers/Value/boolean.h"
#include "Analysis/Structure/Wrappers/Value/character.h"
#include "Analysis/Structure/Wrappers/Reference/string.h"
#include "Exceptions/Compilation/transpile_file_exception.h"

using namespace std;
namespace fs = std::filesystem;

using namespace Services;

using namespace Exceptions;

using namespace Lexing;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Statements;

using namespace Parsing;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

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

    name = path.filename().string();
    source = new SourceDirectory(name, true);

    ExceptionManager::Instance();
    PushStructure(sourcePath, source);
}

void Compiler::Transpile() const
{
    const auto outputDirectory = fs::path(std::format("{}/{}/bin", sourcePath, name));
    if (!exists(outputDirectory))
    {
        if (create_directories(outputDirectory))
            std::cout << "Output directory created: " << outputDirectory << std::endl;
        else
        {
            ExceptionManager::Instance().AddChild(new TranspileFileException(outputDirectory));
            return;
        }
    }

    const auto outputFile = outputDirectory / fs::path(name + (Entrypoint::Instance() == nullptr ? ".dll" : ".exe"));
    std::ofstream file(outputFile);
    if (!file.is_open())
    {
        ExceptionManager::Instance().AddChild(new TranspileFileException(outputFile));
        return;
    }

    file.close();

    StringBuilder stringBuilder;

    stringBuilder.PushLine(std::format(".assembly {} {}", name, "{}"));
    stringBuilder.PushLine(".assembly extern mscorelib");
    stringBuilder.PushLine(".assembly extern System.Runtime {}");
    stringBuilder.PushLine(".assembly extern System.Collections.Generic.Runtime {}");

    source->Transpile(stringBuilder);

    if (!ExceptionManager::Instance().LogAllExceptions())
        std::cout << "Compiled successfully at: " << outputFile << std::endl;
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
    //steps.push_back(&SourceObject::BindGlobal);
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

        source->Print("", true);

        //Transpile();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    delete source;
}
