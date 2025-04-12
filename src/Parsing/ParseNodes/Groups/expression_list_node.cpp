#include "expression_list_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    ExpressionListNode::ExpressionListNode(const Tokens::Token& token) : DynamicNodeCollection(token)
    { }

    NodeType ExpressionListNode::NodeType() const { return NodeType::ExpressionList; }

    void ExpressionListNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Expression List Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}
