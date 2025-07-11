#include "explicit_cast_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Creation
{
    ExplicitCastNode::ExplicitCastNode(const IParseNode* const describer, const IParseNode* const type, const IParseNode* const parameters, const IParseNode* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword)
    {
        AddChild(ChildCode::Describer, describer);
        AddChild(ChildCode::Type, type);
        AddChild(ChildCode::Parameters, parameters);
        AddChild(ChildCode::Body, body);
    }

    NodeType ExplicitCastNode::NodeType() const { return NodeType::ExplicitDeclaration; }

    void ExplicitCastNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Explicit Cast Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Describer))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Type))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Parameters))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Body))->Print(indent + next, true);
    }
}
