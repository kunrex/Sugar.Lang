#include "compiler.h"

#include <format>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "Exceptions/exception_manager.h"
#include "Exceptions/Compilation/source_file_exception.h"
#include "Exceptions/Compilation/transpile_file_exception.h"

#include "Lexing/Lexer/lexer.h"

#include "Parsing/Parser/parser.h"

#include "Analysis/Creation/Transpiling/cil_transpiler.h"

#include "Analysis/Structure/Wrappers/Value/long.h"
#include "Analysis/Structure/Wrappers/Value/float.h"
#include "Analysis/Structure/Wrappers/Value/short.h"
#include "Analysis/Structure/Wrappers/Value/double.h"
#include "Analysis/Structure/Wrappers/Value/integer.h"
#include "Analysis/Structure/Wrappers/Value/boolean.h"
#include "Analysis/Structure/Wrappers/Reference/void.h"
#include "Analysis/Structure/Wrappers/Reference/math.h"
#include "Analysis/Structure/Wrappers/Value/character.h"
#include "Analysis/Structure/Wrappers/Reference/string.h"
#include "Analysis/Structure/Wrappers/Reference/object.h"
#include "Analysis/Structure/Wrappers/Reference/exception.h"
#include "Analysis/Structure/Global/Functions/void_function.h"

namespace fs = std::filesystem;

using namespace Services;

using namespace Exceptions;

using namespace Lexing;

using namespace Parsing;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Wrappers;

constexpr std::string_view source_extension = ".sugar";

void PushStructure(const std::string& strPath, SourceDirectory* const directory)
{
    const auto path = fs::path(strPath);

    if (!exists(path) || !is_directory(path))
    {
        ExceptionManager::PushException(SourceFileException(path));
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
                ExceptionManager::PushException(SourceFileException(childPath));
                return;
            }

            const auto clippedName = name.substr(0, name.find_last_of('.'));
            directory->AddChild(clippedName, new SourceFile(clippedName, std::string((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>())));
        }
    }
}

Compiler::Compiler(const std::string& sourcePath) : sourcePath(sourcePath)
{
    const fs::path path = sourcePath;
    if (!exists(path) || !is_directory(path))
    {
        ExceptionManager::PushException(SourceFileException(path));
        return;
    }

    name = path.filename().string();
    source = new SourceDirectory(name, true);

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
            ExceptionManager::PushException(TranspileFileException(outputDirectory));
            return;
        }
    }

    const auto outputFile = outputDirectory / fs::path(name + ".il");
    std::ofstream file(outputFile);
    if (!file.is_open())
    {
        ExceptionManager::PushException(TranspileFileException(outputFile));
        return;
    }

    file.close();

    StringBuilder stringBuilder(outputFile);

    stringBuilder.PushLine(std::string_view(".assembly extern System.Runtime {}"));
    stringBuilder.PushLine(std::string_view(".assembly extern System.Console {}"));
    stringBuilder.PushLine(std::string_view(".assembly extern System.Collections.Generic.Runtime {}"));

    stringBuilder.PushLine(std::string_view());
    stringBuilder.PushLine(std::format(".assembly {} {}", name, "{}"));
    stringBuilder.PushLine(std::format(".module {}.{}", name, Entrypoint::Instance() == nullptr ? "dll" : "exe"));

    stringBuilder.WriteToFile();
    source->Transpile(stringBuilder);

    if (!ExceptionManager::LogAllExceptions())
        std::cout << "Compiled successfully at: " << outputFile << std::endl;
}

void Compiler::Compile() const
{
    if (ExceptionManager::LogAllExceptions())
    {
        std::cout << "Failed to initialise source system." << std::endl;
        return;
    }

    Lexer::Instance();
    Parser::Instance();

    std::vector<void(SourceObject::*)()> steps;
    steps.push_back(&SourceObject::LexParse);
    steps.push_back(&SourceObject::InitDataTypes);
    steps.push_back(&SourceObject::ManageImports);

    try
    {
        for (const auto func: steps)
        {
            (source->*func)();

            if (ExceptionManager::LogAllExceptions())
            {
                delete source;
                return;
            }
        }

        Short::BindGlobalInstance();
        Integer::BindGlobalInstance();
        Long::BindGlobalInstance();
        Float::BindGlobalInstance();
        Double::BindGlobalInstance();
        Boolean::BindGlobalInstance();
        Character::BindGlobalInstance();
        String::BindGlobalInstance();
        Exception::BindGlobalInstance();
        Void::BindGlobalInstance();
        Object::BindGlobalInstance();
        Math::BindGlobalInstance();

        source->BindGlobal();
        if (ExceptionManager::LogAllExceptions())
        {
            delete source;
            return;
        }

        source->BindLocal();
        if (ExceptionManager::LogAllExceptions())
        {
            delete source;
            return;
        }

        Transpile();
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    delete source;
}
