#include "array_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Types
{
    ArrayTypeNode::ArrayTypeNode(const Token& keyword, const GenericNode* generic) : GenericTypeNode(keyword, generic)
    { }

    NodeType ArrayTypeNode::NodeType() const { return NodeType::ArrayType; }
}