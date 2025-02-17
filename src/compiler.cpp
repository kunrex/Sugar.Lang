#include "compiler.h"

#include <fstream>
#include <sstream>
#include <filesystem>

#include "Analysis/project_initializer.h"
#include "Analysis/Creation/Transpiling/cil_transpiler.h"
#include "Lexing/Lexer/lexer.h"
#include "Exceptions/exception_manager.h"
#include "Analysis/Structure/source_file.h"
#include "Analysis/Structure/Enums/describer.h"
#include "Analysis/Structure/Nodes/DataTypes/class.h"
#include "Analysis/Structure/Nodes/DataTypes/enum.h"
#include "Analysis/Structure/Nodes/DataTypes/struct.h"
#include "Exceptions/Compiling/source_file_exception.h"
#include "Exceptions/Compiling/Analysis/duplicate_structure_definition.h"
#include "Exceptions/Compiling/Analysis/invalid_describer_exception.h"
#include "Exceptions/Compiling/Analysis/invalid_import_path_exception.h"
#include "Parsing/ParseNodes/DataTypes/data_type_node.h"
#include "Parsing/ParseNodes/Statements/import_statement_node.h"
#include "Parsing/Parser/parser.h"

using namespace std;
namespace fs = std::filesystem;

using namespace Exceptions;

using namespace Lexing;

using namespace ParseNodes::Enums;
using namespace ParseNodes::DataTypes;
using namespace ParseNodes::Statements;

using namespace Parsing;

using namespace Analysis::Creation;

using namespace Analysis::Structure;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::DataTypes;

constexpr string_view source_extension = ".sugar";

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
            directory->Push(name, child);

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

            directory->Push(name, new SourceFile(name, string((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>())));
        }
    }
}

void Compiler::LexParse(SourceObject* const directory)
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

void Compiler::StructureDataTypes(const SourceDirectory* const directory)
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

void Compiler::ManageImportStatements(const SourceDirectory* const directory)
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
                    {
                        const auto importNode = dynamic_cast<const ImportStatementNode*>(node);
                        ImportStatement(*importNode, file);
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

void Compiler::BindGlobal(const SourceDirectory* directory)
{
    for (const auto child: directory->values())
    {
        if (child->SourceType() == SourceType::Directory)
        {
            ManageImportStatements(dynamic_cast<SourceDirectory*>(child));
            continue;
        }

        const auto file = dynamic_cast<SourceFile*>(child);
        for (const auto type: file->values())
            BindDataTypeGlobal(type);
    }
}

void Compiler::BindLocal(const SourceDirectory* directory)
{
    for (const auto child: directory->values())
    {
        if (child->SourceType() == SourceType::Directory)
        {
            ManageImportStatements(dynamic_cast<SourceDirectory*>(child));
            continue;
        }

        const auto file = dynamic_cast<SourceFile*>(child);
        for (const auto type: file->values())
            BindDataTypeLocal(type);
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

    StructureDataTypes(source);
    if (ExceptionManager::Instance().ChildCount() > 0)
    {
        delete source;
        return;
    }

    ManageImportStatements(source);

    if (ExceptionManager::Instance().ChildCount() > 0)
    {
        delete source;
        return;
    }

    BindGlobal(source);

    if (ExceptionManager::Instance().ChildCount() > 0)
    {
        delete source;
        return;
    }

    BindLocal(source);

    if (ExceptionManager::Instance().ChildCount() > 0)
    {
        delete source;
        return;
    }

    const auto

    const auto transpiler = CILTranspiler(source->Name(), );
    //yayyy
}