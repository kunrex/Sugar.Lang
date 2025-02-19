#include "dot_expression_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    DotExpressionNode::DotExpressionNode(const ParseNode* const lhs, const ParseNode* const rhs) : ParseNode(), lhs(lhs), rhs(rhs)
    { }

    NodeType DotExpressionNode::NodeType() const { return NodeType::Dot; }

    const ParseNode* DotExpressionNode::LHS() const { return lhs; }
    const ParseNode* DotExpressionNode::RHS() const { return rhs; }

    unsigned long DotExpressionNode::Index() const { return lhs->Index(); }

    DotExpressionNode::~DotExpressionNode()
    {
        delete lhs;
        delete rhs;
    }
}
