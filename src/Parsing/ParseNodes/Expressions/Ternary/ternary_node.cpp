#include "ternary_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    TernaryNode::TernaryNode(const ParseNode* const condition, const ParseNode* const trueValue, const ParseNode* const falseValue) : ParseNode(), condition(condition), trueValue(trueValue), falseValue(falseValue)
    { }

    NodeType TernaryNode::NodeType() const { return NodeType::Ternary; }

    const ParseNode* TernaryNode::Condition() const { return condition; }

    const ParseNode* TernaryNode::True() const { return trueValue; }
    const ParseNode* TernaryNode::False() const { return condition; }

    unsigned long TernaryNode::Index() const { return condition->Index(); }

    TernaryNode::~TernaryNode()
    {
        delete condition;

        delete trueValue;
        delete falseValue;
    }
}
