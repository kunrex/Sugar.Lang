#include "func_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    FuncTypeNode::FuncTypeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType FuncTypeNode::NodeType() const { return NodeType::FuncType; }
}
