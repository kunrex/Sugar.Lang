#include "loop_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Loops
{
    LoopNode::LoopNode(const ParseNode* const condition, const DynamicNodeCollection* const body, const Tokens::Token& keyword) : FixedNodeCollection<2>(keyword), BodyNode(body)
    {
        AddChild(ChildCode::Expression, condition);
    }
}
