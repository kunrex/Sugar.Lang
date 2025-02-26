#include "condition_node.h"

using namespace Tokens;

namespace ParseNodes::Conditions
{
    ConditionNode::ConditionNode(const ParseNode* const condition, const NodeCollection<ParseNode>* const body, const Token& keyword) : ParseNode(), BodyNode(body), condition(condition), keyword(keyword)
    { }

    const ParseNode* ConditionNode::Condition() const { return condition; }

    unsigned long ConditionNode::Index() const { return keyword.Index(); }

    ConditionNode::~ConditionNode()
    {
        delete condition;
    }
}
