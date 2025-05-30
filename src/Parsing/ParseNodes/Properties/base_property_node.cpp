#include "base_property_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    BasePropertyNode::BasePropertyNode(const DescriberNode* const describer, const IParseNode* type, const IdentifierNode* identifier, const IParseNode* const get, const IParseNode* const set) : FixedNodeCollection(identifier->Token())
    {
        AddChild(ChildCode::Describer, describer);
        AddChild(ChildCode::Type, type);
        AddChild(ChildCode::Identifier, identifier);
        AddChild(ChildCode::Get, get);
        AddChild(ChildCode::Set, set);
    }

    NodeType BasePropertyNode::NodeType() const { return NodeType::Property; }

    void BasePropertyNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Property Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Describer))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Type))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Identifier))->Print(indent + next, false);

        if (const auto get = GetChild(static_cast<int>(ChildCode::Get)); get != nullptr)
            get->Print(indent + next, false);

        if (const auto set = GetChild(static_cast<int>(ChildCode::Set)); set != nullptr)
            set->Print(indent + next, true);
    }
}
