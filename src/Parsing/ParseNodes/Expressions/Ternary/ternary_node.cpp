#include "ternary_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    TernaryNode::TernaryNode(const ParseNode* condition, const ParseNode* trueValue, const ParseNode* falseValue) : ParseNode(), condition(condition), trueValue(trueValue), falseValue(falseValue)
    { }

    NodeType TernaryNode::NodeType() const { return NodeType::Ternary; }

    const ParseNode* TernaryNode::Condition() const { return condition; }

    const ParseNode* TernaryNode::True() const { return trueValue; }
    const ParseNode* TernaryNode::False() const { return condition; }

    TernaryNode::~TernaryNode()
    {
        delete condition;

        delete trueValue;
        delete falseValue;
    }
}
