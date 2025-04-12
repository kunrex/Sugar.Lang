#include "dot_expression_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    DotExpressionNode::DotExpressionNode(const IParseNode* const lhs, const IParseNode* const rhs, const Tokens::Token& dot) : FixedNodeCollection(dot)
    {
        AddChild(ChildCode::LHS, lhs);
        AddChild(ChildCode::RHS, rhs);
    }

    NodeType DotExpressionNode::NodeType() const { return NodeType::Dot; }

    void DotExpressionNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Dot Expression Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::LHS))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::RHS))->Print(indent + next, true);
    }
}
