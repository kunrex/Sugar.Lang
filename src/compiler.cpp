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

using namespace std;
namespace fs = std::filesystem;

using namespace Exceptions;

using namespace Lexing;

using namespace ParseNodes::Enums;
using namespace ParseNodes::DataTypes;
using namespace ParseNodes::Statements;

using namespace Parsing;

using namespace Analysis::Creation;
using namespace Analysis::Creation::Binding;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Enums;

constexpr string_view source_extension = ".sugar";

void PushDirectory(const std::string& strPath, SourceDirectory* const directory)
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
            directory->AddChild(name, child);

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

            directory->AddChild(name, new SourceFile(name, string((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>())));
        }
    }
}

void LexParse(SourceObject* const directory)
{
    for (const auto child: *directory)
    {
        if (child->SourceType() == SourceType::Directory)
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

void StructureDataTypes(const SourceDirectory* const directory)
{
    for (const auto child: directory->values())
    {
        if (child->SourceType() == SourceType::Directory)
        {
            StructureDataTypes(dynamic_cast<SourceDirectory*>(child));
            continue;
        }

        const auto file = dynamic_cast<SourceFile*>(child);
        for (const auto source = file->SourceNode(); const auto node: *source)
        {
            switch (node->NodeType())
            {
                case NodeType::Enum:
                    CreateEnum(dynamic_cast<const DataTypeNode*>(node), file);
                    break;
                case NodeType::Class:
                    CreateClass(dynamic_cast<const DataTypeNode*>(node), file);
                    break;
                case NodeType::Struct:
                    CreateStruct(dynamic_cast<const DataTypeNode*>(node), file);
                    break;
                default:
                    break;
            }
        }
    }
}

void ManageImportStatements(const SourceDirectory* const directory)
{
    for (const auto child: directory->values())
    {
        if (child->SourceType() == SourceType::Directory)
        {
            ManageImportStatements(dynamic_cast<SourceDirectory*>(child));
            continue;
        }

        const auto file = dynamic_cast<SourceFile*>(child);
        for (const auto sourceNode = file->SourceNode(); const auto node: *sourceNode)
        {
            switch (node->NodeType())
            {
                case NodeType::Enum:
                case NodeType::Class:
                case NodeType::Struct:
                    break;
                case NodeType::Import:
                    ImportStatement(dynamic_cast<const ImportStatementNode*>(node), file);
                    break;
                default:
                    ExceptionManager::Instance().AddChild(new LogException("Project scopes can only contain import statements and type definitions", node->Index(), file));
                    break;
            }
        }
    }
}

void BindGlobal(const SourceDirectory* directory)
{
    for (const auto child: directory->values())
    {
        if (child->SourceType() == SourceType::Directory)
        {
            BindGlobal(dynamic_cast<SourceDirectory*>(child));
            continue;
        }

        GlobalBindSourceFile(dynamic_cast<SourceFile*>(child));
    }
}

void BindLocal(const SourceDirectory* directory)
{
    for (const auto child: directory->values())
    {
        if (child->SourceType() == SourceType::Directory)
        {
            BindLocal(dynamic_cast<SourceDirectory*>(child));
            continue;
        }

        LocalBindSourceFile(dynamic_cast<SourceFile*>(child));
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
    source = new SourceDirectory(name);

    ExceptionManager::Instance();
    PushDirectory(sourcePath, source);
}

void Compiler::Compile() const
{
    if (ExceptionManager::Instance().ChildCount() > 0)
        return;

    Lexer::Instance();
    Parser::Instance();
    LexParse(source);

    std::vector<void (*)(const SourceDirectory*)> steps;
    steps.push_back(StructureDataTypes);
    steps.push_back(ManageImportStatements);
    steps.push_back(BindGlobal);
    steps.push_back(BindLocal);

    for (const auto func : steps)
    {
        func(source);

        if (ExceptionManager::Instance().LogAllExceptions())
        {
            delete source;
            return;
        }
    }

    const CILTranspiler transpiler(name, sourcePath, source);
    transpiler.Transpile();

    if (!ExceptionManager::Instance().LogAllExceptions())
        cout << "Compiled successfully at " << transpiler.OutputFile() << endl;

    delete source;
}
