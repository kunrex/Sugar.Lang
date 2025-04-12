#include "for_loop_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Loops
{
    ForLoopNode::ForLoopNode(const IParseNode* const pre, const IParseNode* const condition, const IParseNode* const post, const DynamicNodeCollection* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword)
    {
        AddChild(ChildCode::Expression, condition);
        AddChild(ChildCode::Pre, pre);
        AddChild(ChildCode::Post, post);
        AddChild(ChildCode::Body, body);
    }

    NodeType ForLoopNode::NodeType() const { return NodeType::For; }

    void ForLoopNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "For Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Pre))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Expression))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Post))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Body))->Print(indent + next, true);
    }
}
