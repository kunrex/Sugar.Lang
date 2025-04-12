#include "func_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    FuncTypeNode::FuncTypeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType FuncTypeNode::NodeType() const { return NodeType::FuncType; }

    void FuncTypeNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Func Type Node" << std::endl;
        const auto next = indent + (last ? " " : "| ");

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(next, ++i == childCount);
    }
}
