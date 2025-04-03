#include "indexer_expression_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    IndexerExpressionNode::IndexerExpressionNode(const ParseNode* const operand) : DynamicNodeCollection(operand->Token())
    {
        AddChild(operand);
    }

    NodeType IndexerExpressionNode::NodeType() const { return NodeType::Indexer; }
}
