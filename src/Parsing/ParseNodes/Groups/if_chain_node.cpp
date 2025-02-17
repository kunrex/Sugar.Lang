#include "if_chain_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    IfChainNode::IfChainNode() : NodeCollection()
    { }

    NodeType IfChainNode::NodeType() const { return NodeType::IfChain; }

    unsigned long IfChainNode::Index() const
    {
        if (!children.empty())
            return children[0]->Index();

        return 0;
    }
}

