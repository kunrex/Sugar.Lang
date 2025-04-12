#include "constructor_creation_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    ConstructorCreationNode::ConstructorCreationNode(const DescriberNode* const describer, const CompoundDeclarationNode* const parameters, const DynamicNodeCollection* const body, const Tokens::Token& keyword) : FixedNodeCollection(keyword)
    {
        AddChild(ChildCode::Describer, describer);
        AddChild(ChildCode::Parameters, parameters);
        AddChild(ChildCode::Body, body);
    }

    NodeType ConstructorCreationNode::NodeType() const { return NodeType::ConstructorDeclaration; }

    void ConstructorCreationNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Constructor Creation Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Describer))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Parameters))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Body))->Print(indent + next, true);
    }
}

