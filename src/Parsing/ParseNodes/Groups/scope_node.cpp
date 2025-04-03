#include "scope_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    ScopeNode::ScopeNode(const Tokens::Token& token) : DynamicNodeCollection(token)
    { }

    NodeType ScopeNode::NodeType() const { return NodeType::Scope; }
}
