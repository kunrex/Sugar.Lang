#include "scope_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    ScopeNode::ScopeNode() : NodeCollection()
    { }

    NodeType ScopeNode::NodeType() const { return NodeType::Scope; }
}
