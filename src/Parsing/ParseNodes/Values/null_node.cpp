#include "null_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Values
{
    NullNode::NullNode(const Token& keyword) : ValueNode(keyword)
    { }

    NodeType NullNode::NodeType() const { return NodeType::Null; }
}