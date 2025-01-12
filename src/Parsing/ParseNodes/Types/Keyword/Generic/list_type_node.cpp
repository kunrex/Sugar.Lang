#include "list_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Types
{
    ListTypeNode::ListTypeNode(const Token& keyword, const GenericNode* generic) : GenericTypeNode(keyword, generic)
    { }

    NodeType ListTypeNode::NodeType() const { return NodeType::ListType; }
}
