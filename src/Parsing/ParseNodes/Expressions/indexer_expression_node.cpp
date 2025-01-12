#include "indexer_expression_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;

namespace ParseNodes::Expressions
{
    IndexerExpressionNode::IndexerExpressionNode(const ParseNode* operand) : NodeCollection(), operand(operand)
    { }

    NodeType IndexerExpressionNode::NodeType() const { return NodeType::Indexer; }

    const ParseNode* IndexerExpressionNode::Operand() const { return operand; }

    IndexerExpressionNode::~IndexerExpressionNode()
    {
        delete operand;
    }
}
