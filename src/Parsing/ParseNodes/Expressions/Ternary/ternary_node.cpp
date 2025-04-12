#include "ternary_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Expressions
{
    TernaryNode::TernaryNode(const IParseNode* const condition, const IParseNode* const trueValue, const IParseNode* const falseValue, const Tokens::Token& questionMark) : FixedNodeCollection(questionMark)
    {
        AddChild(ChildCode::Expression, condition);
        AddChild(ChildCode::LHS, trueValue);
        AddChild(ChildCode::RHS, falseValue);
    }

    NodeType TernaryNode::NodeType() const { return NodeType::Ternary; }

    void TernaryNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Ternary Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Expression))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::LHS))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::RHS))->Print(indent + next, true);
    }
}
