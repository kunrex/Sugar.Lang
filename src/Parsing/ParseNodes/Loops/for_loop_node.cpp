#include "for_loop_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Loops
{
    ForLoopNode::ForLoopNode(const ParseNode* const pre, const ParseNode* const condition, const ParseNode* const post, const ScopeNode* const body, const Token& keyword) : LoopNode(condition, body, keyword), pre(pre), post(post)
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
