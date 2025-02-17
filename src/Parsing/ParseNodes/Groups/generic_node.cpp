#include "generic_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    GenericNode::GenericNode(const unsigned long index) : NodeCollection(), index(index)
    { }

    NodeType GenericNode::NodeType() const { return NodeType::Generic; }

    unsigned long GenericNode::Index() const { return index; }
}
