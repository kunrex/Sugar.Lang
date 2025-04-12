#include "copy_coll_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    CopyCallNode::CopyCallNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType CopyCallNode::NodeType() const { return NodeType::Copy; }

    void CopyCallNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Copy Call Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}