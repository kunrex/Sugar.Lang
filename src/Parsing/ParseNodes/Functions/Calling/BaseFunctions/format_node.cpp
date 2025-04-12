#include "format_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    FormatNode::FormatNode(const Tokens::Token& keyword) :  DynamicNodeCollection(keyword)
    { }

    NodeType FormatNode::NodeType() const { return NodeType::Format; }

    void FormatNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Format Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}
