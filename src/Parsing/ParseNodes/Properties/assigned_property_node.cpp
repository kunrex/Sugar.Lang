#include "assigned_property_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    AssignedPropertyNode::AssignedPropertyNode(const DescriberNode* const describer, const IParseNode* const type, const IdentifierNode* const identifier, const GetNode* const get, const SetNode* const set, const IParseNode* const value) : FixedNodeCollection(identifier->Token())
    {
        AddChild(ChildCode::Describer, describer);
        AddChild(ChildCode::Type, type);
        AddChild(ChildCode::Identifier, identifier);
        AddChild(ChildCode::Get, get);
        AddChild(ChildCode::Set, set);
        AddChild(ChildCode::Expression, value);
    }

    NodeType AssignedPropertyNode::NodeType() const { return NodeType::PropertyInitialisation; }

    void AssignedPropertyNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Property Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Describer))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Type))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Identifier))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Get))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Set))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Expression))->Print(indent + next, true);
    }
}
