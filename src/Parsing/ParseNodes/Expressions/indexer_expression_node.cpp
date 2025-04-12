#include "indexer_expression_node.h"

using namespace ParseNodes::Enums;
using namespace ParseNodes::Core::Interfaces;

namespace ParseNodes::Expressions
{
    IndexerExpressionNode::IndexerExpressionNode(const IParseNode* const operand) : DynamicNodeCollection(operand->Token())
    {
        AddChild(operand);
    }

    NodeType IndexerExpressionNode::NodeType() const { return NodeType::Indexer; }

    void IndexerExpressionNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Indexer Expression Node" << std::endl;
        const auto next = last ? " " : "| ";

        auto i = 0;
        const auto childCount = children.size();
        for (const auto child: children)
            child->Print(indent + next, ++i == childCount);
    }
}
