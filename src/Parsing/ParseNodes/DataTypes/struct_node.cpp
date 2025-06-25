#include "struct_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::DataTypes
{
    StructNode::StructNode(const IParseNode* const describer, const IParseNode* const identifier, const IParseNode* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword)
    {
        AddChild(ChildCode::Describer, describer);
        AddChild(ChildCode::Identifier, identifier);
        AddChild(ChildCode::Body, body);
    }

    NodeType StructNode::NodeType() const { return NodeType::Struct; }

    void StructNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Struct Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Describer))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Identifier))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Body))->Print(indent + next, true);
    }
}

