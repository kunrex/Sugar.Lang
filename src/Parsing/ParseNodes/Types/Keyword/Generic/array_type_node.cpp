#include "array_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    ArrayTypeNode::ArrayTypeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType ArrayTypeNode::NodeType() const { return NodeType::ArrayType; }
}