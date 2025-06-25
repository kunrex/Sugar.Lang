#include "initialisation_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Statements
{
    InitialisationNode::InitialisationNode(const IParseNode* const describer, const IParseNode* const type, const IParseNode* const identifier, const IParseNode* const value, const Tokens::Token& separator) : FixedNodeCollection(separator)
    {
        AddChild(ChildCode::Describer, describer);
        AddChild(ChildCode::Type, type);
        AddChild(ChildCode::Identifier, identifier);
        AddChild(ChildCode::Expression, value);
    }

    NodeType InitialisationNode::NodeType() const { return NodeType::Initialisation; }

    void InitialisationNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Initialisation Statement Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Describer))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Type))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Identifier))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Expression))->Print(indent + next, true);
    }
}
