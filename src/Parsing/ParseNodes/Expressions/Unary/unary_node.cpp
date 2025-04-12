#include "unary_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    UnaryNode::UnaryNode(const Tokens::Token& base, const IParseNode* const operand) : FixedNodeCollection(base)
    {
        AddChild(ChildCode::Expression, operand);
    }

    NodeType UnaryNode::NodeType() const { return NodeType::Unary; }

    void UnaryNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Unary Node: " << ToString(token.Kind()) << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Expression))->Print(indent + next, false);
    }
}
