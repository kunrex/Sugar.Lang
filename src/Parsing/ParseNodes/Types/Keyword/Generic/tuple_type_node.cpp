#include "tuple_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    TupleTypeNode::TupleTypeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType TupleTypeNode::NodeType() const { return NodeType::TupleType; }
}