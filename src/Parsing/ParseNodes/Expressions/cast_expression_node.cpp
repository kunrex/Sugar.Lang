#include "cast_expression_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    CastExpressionNode::CastExpressionNode(const ParseNode* const lhs, const ParseNode* const rhs, const Tokens::Token& as) : DotExpressionNode(lhs, rhs, as)
    { }

    NodeType CastExpressionNode::NodeType() const { return NodeType::Cast; }
}
