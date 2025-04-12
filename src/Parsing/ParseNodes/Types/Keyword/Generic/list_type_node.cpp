#include "list_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    ListTypeNode::ListTypeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType ListTypeNode::NodeType() const { return NodeType::ListType; }

    void ListTypeNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "List Type Node" << std::endl;
        const auto next = indent + (last ? " " : "| ");

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(next, ++i == childCount);
    }
}
