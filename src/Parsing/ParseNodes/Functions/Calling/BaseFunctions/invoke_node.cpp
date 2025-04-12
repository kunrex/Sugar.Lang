#include "invoke_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    InvokeNode::InvokeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType InvokeNode::NodeType() const { return NodeType::Invoke; }

    void InvokeNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Invoke Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}
