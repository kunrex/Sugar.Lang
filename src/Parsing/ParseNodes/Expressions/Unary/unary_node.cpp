#include "unary_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    UnaryNode::UnaryNode(const Tokens::Token& base, const ParseNode* operand) : OperatorExpressionNode(base), operand(operand)
    { }

    NodeType UnaryNode::NodeType() const { return NodeType::Unary; }

    const ParseNode* UnaryNode::Operand() const { return operand; }

    UnaryNode::~UnaryNode()
    {
        delete operand;
    }
}
