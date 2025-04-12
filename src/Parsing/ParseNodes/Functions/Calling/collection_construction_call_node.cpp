#include "collection_construction_call_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Calling
{
    CollectionConstructorCallNode::CollectionConstructorCallNode(const IParseNode* const type, const Tokens::Token& keyword) : DynamicNodeCollection(keyword)
    {
        AddChild(type);
    }

    NodeType CollectionConstructorCallNode::NodeType() const { return NodeType::CollectionConstructorCall; }

    void CollectionConstructorCallNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Collection Constructor Call Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}

