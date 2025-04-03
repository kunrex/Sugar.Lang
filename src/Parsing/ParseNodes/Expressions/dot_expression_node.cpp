#include "dot_expression_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    DotExpressionNode::DotExpressionNode(const ParseNode* const lhs, const ParseNode* const rhs, const Tokens::Token& dot) : FixedNodeCollection(dot)
    {
        AddChild(ChildCode::LHS, lhs);
        AddChild(ChildCode::RHS, rhs);
    }

    NodeType DotExpressionNode::NodeType() const { return NodeType::Dot; }
}
