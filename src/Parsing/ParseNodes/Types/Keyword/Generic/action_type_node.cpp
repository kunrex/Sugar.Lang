#include "action_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Types
{
    ActionTypeNode::ActionTypeNode(const Token& keyword, const GenericNode* generic) : GenericTypeNode(keyword, generic)
    { }

    NodeType ActionTypeNode::NodeType() const { return NodeType::ActionType; }
}
