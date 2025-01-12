#include "invalid_node.h"

using namespace std;

using namespace ParseNodes::Enums;

namespace ParseNodes
{
    InvalidNode::InvalidNode() : NodeCollection()
    { }

    NodeType InvalidNode::NodeType() const { return NodeType::Invalid; }
}
