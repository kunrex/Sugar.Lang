#include "if_chain_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    IfChainNode::IfChainNode(const Tokens::Token& token) : DynamicNodeCollection(token)
    { }

    NodeType IfChainNode::NodeType() const { return NodeType::IfChain; }

    void IfChainNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "If Chain Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}

