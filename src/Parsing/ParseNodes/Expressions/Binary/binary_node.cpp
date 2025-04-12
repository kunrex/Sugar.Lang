#include "binary_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    BinaryNode::BinaryNode(const Tokens::Token& base, const IParseNode* const lhs, const IParseNode* const rhs) : FixedNodeCollection<2>(base)
    {
        AddChild(ChildCode::LHS, lhs);
        AddChild(ChildCode::RHS, rhs);
    }

    NodeType BinaryNode::NodeType() const { return NodeType::Binary; }

    void BinaryNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Binary Node: " << ToString(token.Kind()) << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::LHS))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::RHS))->Print(indent + next, true);
    }
}
