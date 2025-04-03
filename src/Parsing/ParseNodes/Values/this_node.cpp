#include "this_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Values
{
    ThisNode::ThisNode(const Tokens::Token& keyword) : ParseNode(keyword)
    { }

    NodeType ThisNode::NodeType() const { return NodeType::This; }
}