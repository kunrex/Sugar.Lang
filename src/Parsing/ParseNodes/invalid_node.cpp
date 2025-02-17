#include "invalid_node.h"

using namespace std;

using namespace ParseNodes::Enums;

namespace ParseNodes
{
    InvalidNode::InvalidNode(const unsigned long index) : NodeCollection(), index(index)
    { }

    NodeType InvalidNode::NodeType() const { return NodeType::Invalid; }

    unsigned long InvalidNode::Index() const { return index; }
}
