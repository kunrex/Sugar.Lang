#include "declaration_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    DeclarationNode::DeclarationNode(const IParseNode* const describer, const IParseNode* const type, const IParseNode* const identifier, const Tokens::Token& separator) : FixedNodeCollection(separator)
    {
        AddChild(ChildCode::Describer, describer);
        AddChild(ChildCode::Type, type);
        AddChild(ChildCode::Identifier, identifier);
    }

    NodeType DeclarationNode::NodeType() const { return NodeType::Declaration; }

    void DeclarationNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Declaration Statement Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Describer))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Type))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Identifier))->Print(indent + next, true);
    }
}
