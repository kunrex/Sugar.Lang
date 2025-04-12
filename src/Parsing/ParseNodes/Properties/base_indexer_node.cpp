#include "base_indexer_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Properties
{
    BaseIndexerNode::BaseIndexerNode(const DescriberNode* const describer, const IParseNode* const type, const CompoundDeclarationNode* const parameters, const GetNode* const get, const SetNode* const set, const Tokens::Token& keyword) : FixedNodeCollection(keyword)
    {
        AddChild(ChildCode::Describer, describer);
        AddChild(ChildCode::Type, type);
        AddChild(ChildCode::Parameters, parameters);
        AddChild(ChildCode::Get, get);
        AddChild(ChildCode::Set, set);
    }

    NodeType BaseIndexerNode::NodeType() const { return NodeType::IndexerDeclaration; }

    void BaseIndexerNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Indexer Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Describer))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Type))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Parameters))->Print(indent + next, false);
        if (const auto get = GetChild(static_cast<int>(ChildCode::Get)); get != nullptr)
            get->Print(indent + next, false);

        if (const auto set = GetChild(static_cast<int>(ChildCode::Set)); set != nullptr)
            set->Print(indent + next, true);
    }
}
