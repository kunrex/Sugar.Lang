#include "action_type_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Types
{
    ActionTypeNode::ActionTypeNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType ActionTypeNode::NodeType() const { return NodeType::ActionType; }

    void ActionTypeNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Action Type Node" << std::endl;
        const auto next = indent + (last ? " " : "| ");

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(next, ++i == childCount);
    }
}
