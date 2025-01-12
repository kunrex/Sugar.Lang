#include "tuple_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Types
{
    TupleTypeNode::TupleTypeNode(const Token& keyword, const GenericNode* generic) : GenericTypeNode(keyword, generic)
    { }

    NodeType TupleTypeNode::NodeType() const { return NodeType::TupleType; }
}