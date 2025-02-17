#include "binary_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    BinaryNode::BinaryNode(const Tokens::Token& base, const ParseNode* lhs, const ParseNode* rhs) : OperatorExpressionNode(base), lhs(lhs), rhs(rhs)
    { }

    NodeType BinaryNode::NodeType() const { return NodeType::Binary; }

    const ParseNode* BinaryNode::LHS() const { return lhs; }
    const ParseNode* BinaryNode::RHS() const { return rhs; }

    unsigned long BinaryNode::Index() const { return lhs->Index(); }

    BinaryNode::~BinaryNode()
    {
        delete lhs;
        delete rhs;
    }
}
