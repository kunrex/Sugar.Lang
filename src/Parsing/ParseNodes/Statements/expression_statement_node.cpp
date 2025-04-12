#include "expression_statement_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    ExpressionStatementNode::ExpressionStatementNode(const IParseNode* const expression, const Tokens::Token& separator) : FixedNodeCollection(separator)
    {
        AddChild(ChildCode::Expression, expression);
    }

    NodeType ExpressionStatementNode::NodeType() const { return NodeType::Expression; }

    void ExpressionStatementNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Expression Statement Node" << std::endl;

        GetChild(static_cast<int>(ChildCode::Expression))->Print(indent + (last ? " " : "| "), true);
    }
}
