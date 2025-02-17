#include "loop_node.h"

using namespace Tokens;

namespace ParseNodes::Loops
{
    LoopNode::LoopNode(const ParseNode* condition, const ParseNode* body, const Token& keyword) : BodyNode(body), condition(condition), keyword(keyword)
    { }

    const ParseNode* LoopNode::Condition() const { return condition; }

    unsigned long LoopNode::Index() const { return keyword.Index(); }

    LoopNode::~LoopNode()
    {
        delete condition;
    }
}
