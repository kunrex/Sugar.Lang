#include "source_file.h"


#include "../../Exceptions/log_exception.h"
#include "../../Exceptions/exception_manager.h"

#include "../../Lexing/Lexer/lexer.h"

#include "../../Parsing/Parser/parser.h"

#include "../Creation/Binding/local_binder.h"
#include "../Creation/Binding/global_binder.h"
#include "../Creation/Binding/project_binder.h"

#include "Core/Interfaces/DataTypes/i_user_defined_type.h"

using namespace std;

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
    SourceFile::SourceFile(const string& name, string source) : SourceObject(name), Dictionary(), source(std::move(source)), tokens(), sourceNode(nullptr), references()
    { }

    SourceType SourceFile::SourceType() const { return SourceType::File; }

    bool SourceFile::AddChild(const string key, IUserDefinedType* const value)
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

    const IDataType* SourceFile::GetReference(const string& name) const
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
    const Tokens::Token& SourceFile::TokenAt(const unsigned long i) { return tokens.at(i); }

    void SourceFile::WithSourceNode(SourceFileNode* const source)
    {
        if (sourceNode == nullptr)
            sourceNode = source;
    }
    const SourceFileNode* SourceFile::SourceNode() const { return sourceNode; }

    void SourceFile::LexParse()
    {
        const auto previous = ExceptionManager::Instance().ChildCount();
        Lexer::Instance().Lex(this);

        if (ExceptionManager::Instance().ChildCount() == previous)
        {
            sourceNode = Parser::Instance().Parse(this);
            sourceNode->Print("", true);
        }
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

    void SourceFile::BindGlobal()
    {
        GlobalBindSourceFile(this);
    }

    void SourceFile::BindLocal()
    {
        LocalBindSourceFile(this);
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
                    ExceptionManager::Instance().AddChild(new LogException("Project scopes can only contain import statements and type definitions", node->Token().Index(), this));
                    break;
            }
        }
    }

    void SourceFile::Print(const string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Sugar File: " << name << std::endl;
        const auto next = indent + (last ? " " : "| ");

        string referenceString = "References: ";
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
