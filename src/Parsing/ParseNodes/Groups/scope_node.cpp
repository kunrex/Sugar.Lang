#include "scope_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    ScopeNode::ScopeNode(const unsigned long index) : NodeCollection(), index(index)
    { }

    NodeType ScopeNode::NodeType() const { return NodeType::Scope; }

    unsigned long ScopeNode::Index() const { return index; }
}
