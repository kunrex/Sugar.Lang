#include "anonymous_type_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    AnonymousTypeNode::AnonymousTypeNode(const Tokens::Token& keyword) : KeywordTypeNode(keyword)
    { }

    NodeType AnonymousTypeNode::NodeType() const { return NodeType::AnonymousType; }
}
