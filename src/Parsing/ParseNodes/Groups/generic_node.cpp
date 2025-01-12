#include "generic_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    GenericNode::GenericNode() : NodeCollection()
    { }

    NodeType GenericNode::NodeType() const { return NodeType::Generic; }
}
