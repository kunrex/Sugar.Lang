#include "invalid_node.h"

using namespace std;

using namespace ParseNodes::Enums;

namespace ParseNodes
{
    InvalidNode::InvalidNode(const Tokens::Token& token) : DynamicNodeCollection(token)
    { }

    NodeType InvalidNode::NodeType() const { return NodeType::Invalid; }
}