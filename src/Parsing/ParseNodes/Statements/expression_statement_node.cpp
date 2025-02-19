#include "expression_statement_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ExpressionStatementNode::ExpressionStatementNode(const ParseNode* const expression, const Token& separator) : StatementNode(separator), expression(expression)
    { }

    NodeType ExpressionStatementNode::NodeType() const { return NodeType::Expression; }

    const ParseNode* ExpressionStatementNode::Expression() const { return expression; }

    unsigned long ExpressionStatementNode::Index() const { return expression->Index(); }

    ExpressionStatementNode::~ExpressionStatementNode()
    {
        delete expression;
    }
}
