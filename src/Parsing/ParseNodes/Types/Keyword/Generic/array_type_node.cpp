#include "array_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    ArrayTypeNode::ArrayTypeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType ArrayTypeNode::NodeType() const { return NodeType::ArrayType; }

    void ArrayTypeNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Array Type Node" << std::endl;
        const auto next = indent + (last ? " " : "| ");

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(next, ++i == childCount);
    }
}