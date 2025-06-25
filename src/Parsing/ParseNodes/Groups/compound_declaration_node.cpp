#include "compound_declaration_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    CompoundDeclarationNode::CompoundDeclarationNode(const Tokens::Token& token, const IParseNode* const describer, const IParseNode* const type) : DynamicNodeCollection(token)
    {
        AddChild(describer);
        AddChild(type);
    }

    NodeType CompoundDeclarationNode::NodeType() const { return NodeType::CompoundDeclaration; }

    void CompoundDeclarationNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Compound Declaration Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }

    MultipleDeclarationNode::MultipleDeclarationNode(const Tokens::Token& token) : DynamicNodeCollection(token)
    { }

    NodeType MultipleDeclarationNode::NodeType() const { return NodeType::CompoundDeclaration; }

    void MultipleDeclarationNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Multiple Declaration Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}
