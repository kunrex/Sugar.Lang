#include "condition_node.h"

using namespace Tokens;

namespace ParseNodes::Conditions
{
    ConditionNode::ConditionNode(const ParseNode* condition, const ParseNode* body, const Token& keyword) : ParseNode(), BodyNode(body), condition(condition), keyword(keyword)
    { }

    const ParseNode* ConditionNode::Condition() const { return condition; }

    const Token& ConditionNode::Keyword() const { return keyword; }

    ConditionNode::~ConditionNode()
    {
        delete condition;
    }
}
