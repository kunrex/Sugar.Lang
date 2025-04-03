#include "constant_node.h"

using namespace Tokens::Enums;

using namespace ParseNodes::Enums;

namespace ParseNodes::Constants
{
    ConstantNode::ConstantNode(const Tokens::Token& token) : ParseNode(token)
    { }

    NodeType ConstantNode::NodeType() const { return NodeType::Constant; }
}
