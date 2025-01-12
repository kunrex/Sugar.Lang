#include "operation_expression_node.h"

using namespace Tokens;

namespace ParseNodes::Expressions
{
    OperatorExpressionNode::OperatorExpressionNode(const Token& base) : ParseNode(), base(base)
    { }

    const Token& OperatorExpressionNode::Base() const { return base; }
}
