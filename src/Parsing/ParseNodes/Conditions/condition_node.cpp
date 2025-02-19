#include "condition_node.h"

using namespace Tokens;

using namespace ParseNodes::Groups;

namespace ParseNodes::Conditions
{
    ConditionNode::ConditionNode(const ParseNode* const condition, const ScopeNode* const body, const Token& keyword) : ParseNode(), BodyNode(body), condition(condition), keyword(keyword)
    { }

    const ParseNode* ConditionNode::Condition() const { return condition; }

    unsigned long ConditionNode::Index() const { return keyword.Index(); }

    ConditionNode::~ConditionNode()
    {
        delete condition;
    }
}
