#include "constructor_call_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    ConstructorCallNode::ConstructorCallNode(const IParseNode* const type, const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    {
        AddChild(type);
    }

    NodeType ConstructorCallNode::NodeType() const { return NodeType::ConstructorCall; }

    void ConstructorCallNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Constructor Call Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}
