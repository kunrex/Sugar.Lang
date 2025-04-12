#include "cast_expression_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    CastExpressionNode::CastExpressionNode(const IParseNode* const lhs, const IParseNode* const rhs, const Tokens::Token& as) : FixedNodeCollection(as)
    {
        AddChild(ChildCode::LHS, lhs);
        AddChild(ChildCode::RHS, rhs);
    }

    NodeType CastExpressionNode::NodeType() const { return NodeType::Cast; }

    void CastExpressionNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Cast Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::LHS))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::RHS))->Print(indent + next, true);
    }
}
