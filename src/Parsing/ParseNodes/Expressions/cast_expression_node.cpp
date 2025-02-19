#include "cast_expression_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    CastExpressionNode::CastExpressionNode(const ParseNode* const lhs, const ParseNode* const rhs) : DotExpressionNode(lhs, rhs)
    { }

    NodeType CastExpressionNode::NodeType() const { return NodeType::Cast; }
}
