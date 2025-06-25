#include "while_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Loops
{
    WhileNode::WhileNode(const IParseNode* const condition, const IParseNode* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword)
    {
        AddChild(ChildCode::Expression, condition);
        AddChild(ChildCode::Body, body);
    }

    NodeType WhileNode::NodeType() const { return NodeType::While;}

    void WhileNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "While Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Expression))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Body))->Print(indent + next, true);
    }
}
