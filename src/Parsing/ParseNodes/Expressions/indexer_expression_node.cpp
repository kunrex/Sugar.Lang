#include "indexer_expression_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    IndexerExpressionNode::IndexerExpressionNode(const ParseNode* const operand) : NodeCollection(), operand(operand)
    { }

    NodeType IndexerExpressionNode::NodeType() const { return NodeType::Indexer; }

    const ParseNode* IndexerExpressionNode::Operand() const { return operand; }

    unsigned long IndexerExpressionNode::Index() const { return operand->Index(); }

    IndexerExpressionNode::~IndexerExpressionNode()
    {
        delete operand;
    }
}
