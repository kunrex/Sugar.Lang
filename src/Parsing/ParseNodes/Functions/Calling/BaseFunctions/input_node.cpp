#include "input_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    InputNode::InputNode(const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    { }

    NodeType InputNode::NodeType() const { return NodeType::Input; }

    void InputNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Input Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}
