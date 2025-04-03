#include "ternary_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    TernaryNode::TernaryNode(const ParseNode* const condition, const ParseNode* const trueValue, const ParseNode* const falseValue, const Tokens::Token& questionMark) : FixedNodeCollection(questionMark)
    {
        AddChild(ChildCode::Expression, condition);
        AddChild(ChildCode::LHS, trueValue);
        AddChild(ChildCode::RHS, falseValue);
    }

    NodeType TernaryNode::NodeType() const { return NodeType::Ternary; }
}
