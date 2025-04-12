#include "print_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    PrintNode::PrintNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType PrintNode::NodeType() const { return NodeType::Print; }

    void PrintNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Print Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }

    PrintlnNode::PrintlnNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType PrintlnNode::NodeType() const { return NodeType::Println; }

    void PrintlnNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Println Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(next, ++i == childCount);
    }
}

