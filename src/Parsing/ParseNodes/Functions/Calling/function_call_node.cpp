#include "function_call_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    FunctionCallNode::FunctionCallNode(const IParseNode* const identifier) : DynamicNodeCollection(identifier->Token())
    {
        AddChild(identifier);
    }

    NodeType FunctionCallNode::NodeType() const { return NodeType::FunctionCall; }

    void FunctionCallNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Function Call Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}
