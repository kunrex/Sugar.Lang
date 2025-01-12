#include "for_loop_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Loops
{
    ForLoopNode::ForLoopNode(const ParseNode* pre, const ParseNode* condition, const ParseNode* post, const ParseNode* body, const Token& keyword) : LoopNode(condition, body, keyword), pre(pre), post(post)
    { }

    NodeType ForLoopNode::NodeType() const { return NodeType::For; }

    const ParseNode* ForLoopNode::Pre() const { return pre; }
    const ParseNode* ForLoopNode::Post() const { return post; }

    ForLoopNode::~ForLoopNode()
    {
        delete pre;
        delete post;
    }
}
