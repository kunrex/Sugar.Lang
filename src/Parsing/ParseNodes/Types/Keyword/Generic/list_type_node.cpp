#include "list_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    ListTypeNode::ListTypeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType ListTypeNode::NodeType() const { return NodeType::ListType; }
}
