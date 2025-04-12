#include "else_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Conditions
{
    ElseNode::ElseNode(const DynamicNodeCollection* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword)
    {
        AddChild(ChildCode::Body, body);
    }

    NodeType ElseNode::NodeType() const { return NodeType::Else; }

    void ElseNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Else Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Body))->Print(indent + next, true);
    }
}
