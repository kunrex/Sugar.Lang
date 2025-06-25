#include "source_file.h"

#include "Core/Interfaces/DataTypes/i_user_defined_type.h"

#include "../Creation/Binding/global_binder.h"
#include "../Creation/Binding/project_binder.h"

#include "../../Exceptions/log_exception.h"
#include "../../Exceptions/exception_manager.h"

#include "../../Lexing/Lexer/lexer.h"

#include "../../Parsing/Parser/parser.h"

using namespace Exceptions;

using namespace Lexing;

using namespace Parsing;
using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

using namespace Analysis::Creation::Binding;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure
{
    SourceFile::SourceFile(const std::string& name, std::string source) : SourceObject(name), source(std::move(source)), sourceNode(nullptr)
    { }

    SourceType SourceFile::SourceType() const { return SourceType::File; }

    bool SourceFile::AddChild(const std::string key, IUserDefinedType* const value)
    {
        const auto result = Dictionary::AddChild(key, value);
        if (result)
        {
            value->SetParent(this);
            AddReference(value);
        }

        return result;
    }

    void SourceFile::AddReference(const IDataType* const dataType)
    {
        references[dataType->Name()] = dataType;
    }

    const IDataType* SourceFile::GetReference(const std::string& name) const
    {
        return references.contains(name) ? references.at(name) : nullptr;
    }

    unsigned long SourceFile::SourceLength() const { return source.size(); }
    char SourceFile::SourceAt(const unsigned long i) const { return source.at(i); }

    void SourceFile::PushBackToken(Tokens::Token token)
    {
        tokens.push_back(std::move(token));
    }

    unsigned long SourceFile::TokenCount() const { return tokens.size(); }
    const Tokens::Token& SourceFile::TokenAt(const unsigned long i) const { return tokens.at(i); }

    const SourceFileNode* SourceFile::SourceNode() const { return sourceNode; }

    void SourceFile::LexParse()
    {
        const auto previous = ExceptionManager::ExceptionCount();
        Lexer::Instance().Lex(this);

        if (ExceptionManager::ExceptionCount() == previous)
            sourceNode = Parser::Instance().Parse(this);
    }

    void SourceFile::InitDataTypes()
    {
        const auto childCount = sourceNode->ChildCount();
        for (auto i = 0; i < childCount; i++)
        {
            switch (const auto node = sourceNode->GetChild(i); node->NodeType())
            {
                case NodeType::Enum:
                    CreateEnum(node, this);
                    break;
                case NodeType::Class:
                    CreateClass(node, this);
                    break;
                case NodeType::Struct:
                    CreateStruct(node, this);
                    break;
                default:
                    break;
            }
        }
    }

    void SourceFile::ManageImports()
    {
        const auto childCount = sourceNode->ChildCount();
        for (auto i = 0; i < childCount; i++)
        {
            switch (const auto node = sourceNode->GetChild(i); node->NodeType())
            {
                case NodeType::Enum:
                case NodeType::Class:
                case NodeType::Struct:
                    break;
                case NodeType::Import:
                    ImportStatement(node, this);
                    break;
                default:
                    ExceptionManager::PushException(LogException("Project scopes can only contain import statements and type definitions", node->Token().Index(), this));
                    break;
            }
        }
    }

    void SourceFile::Transpile(Services::StringBuilder& builder) const
    {
        for (const auto child: values())
            child->Transpile(builder);
    }

    void SourceFile::BindGlobal()
    {
        for (const auto type: values())
            type->BindGlobal();
    }

    void SourceFile::BindLocal()
    {
        for (const auto type: values())
            type->BindLocal();
    }

    void SourceFile::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Sugar File: " << name << std::endl;
        const auto next = indent + (last ? " " : "| ");

        std::string referenceString = "References: ";
        auto i = 0;
        for (const auto& reference : references)
            referenceString += reference.second->FullName() + (i == references.size() - 1 ? "" : ", ");

        std::cout << next << (!map.empty() ? "|-" : "\\-") << referenceString << std::endl;

        i = 0;
        const auto childCount = map.size();
        for (const auto& child: map)
            child.second->Print(next, ++i == childCount);
    }

    SourceFile::~SourceFile()
    {
        delete sourceNode;
    }
}
