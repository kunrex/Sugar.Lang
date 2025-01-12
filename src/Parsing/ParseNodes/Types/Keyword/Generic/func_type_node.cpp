#include "func_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Types
{
    FuncTypeNode::FuncTypeNode(const Token& keyword, const Groups::GenericNode* generic) : GenericTypeNode(keyword, generic)
    { }

    NodeType FuncTypeNode::NodeType() const { return NodeType::FuncType; }
}
