#include "for_loop_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Loops
{
    ForLoopNode::ForLoopNode(const ParseNode* const pre, const ParseNode* const condition, const ParseNode* const post, const DynamicNodeCollection* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword), BodyNode(body)
    {
        AddChild(ChildCode::Expression, condition);
        AddChild(ChildCode::Pre, pre);
        AddChild(ChildCode::Post, post);
    }

    NodeType ForLoopNode::NodeType() const { return NodeType::For; }
}
