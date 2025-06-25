#include "invalid_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes
{
    InvalidNode::InvalidNode(const Tokens::Token& token) : DynamicNodeCollection(token)
    { }

    NodeType InvalidNode::NodeType() const { return NodeType::Invalid; }

    void InvalidNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Invalid Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}