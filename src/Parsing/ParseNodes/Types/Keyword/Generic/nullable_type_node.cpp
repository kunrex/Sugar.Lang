#include "nullable_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    NullableTypeNode::NullableTypeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType NullableTypeNode::NodeType() const { return NodeType::NullableType; }
}