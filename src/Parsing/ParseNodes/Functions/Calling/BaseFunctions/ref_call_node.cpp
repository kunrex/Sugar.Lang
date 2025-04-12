#include "ref_call_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    RefCallNode::RefCallNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType RefCallNode::NodeType() const { return NodeType::Ref; }

    void RefCallNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Ref Call Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}