#include "cast_expression_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    CastExpressionNode::CastExpressionNode(const ParseNode* lhs, const ParseNode* rhs) : DotExpressionNode(lhs, rhs)
    { }

    NodeType CastExpressionNode::NodeType() const { return NodeType::Cast; }
}
