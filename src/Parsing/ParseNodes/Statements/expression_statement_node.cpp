#include "expression_statement_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ExpressionStatementNode::ExpressionStatementNode(const ParseNode* const expression, const Tokens::Token& separator) : FixedNodeCollection(separator)
    {
        AddChild(ChildCode::Expression, expression);
    }

    NodeType ExpressionStatementNode::NodeType() const { return NodeType::Expression; }
}
