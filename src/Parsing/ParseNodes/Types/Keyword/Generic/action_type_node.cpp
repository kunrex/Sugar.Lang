#include "action_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    ActionTypeNode::ActionTypeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType ActionTypeNode::NodeType() const { return NodeType::ActionType; }
}
