#include "funcref_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    FuncRefNode::FuncRefNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType FuncRefNode::NodeType() const { return NodeType::FuncRef; }

    void FuncRefNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Funcref Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}