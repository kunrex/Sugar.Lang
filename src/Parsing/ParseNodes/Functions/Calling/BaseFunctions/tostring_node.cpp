#include "tostring_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    ToStringNode::ToStringNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType ToStringNode::NodeType() const { return NodeType::ToString; }

    void ToStringNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "To String Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}