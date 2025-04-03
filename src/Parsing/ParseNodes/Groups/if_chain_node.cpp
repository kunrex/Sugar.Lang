#include "if_chain_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    IfChainNode::IfChainNode(const Tokens::Token& token) : DynamicNodeCollection(token)
    { }

    NodeType IfChainNode::NodeType() const { return NodeType::IfChain; }
}

