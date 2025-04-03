#include "built_in_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    BuiltInTypeNode::BuiltInTypeNode(const Tokens::Token& keyword) : ParseNode(keyword)
    { }

    NodeType BuiltInTypeNode::NodeType() const { return NodeType::BuiltInType; }
}