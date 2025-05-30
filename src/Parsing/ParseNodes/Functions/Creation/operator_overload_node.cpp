#include "operator_overload_node.h"

using namespace Tokens;

using namespace ParseNodes::Enums;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Describers;

namespace ParseNodes::Functions::Creation
{
    OperatorOverloadNode::OperatorOverloadNode(const DescriberNode* const describer, const IParseNode* const type, const Tokens::Token& base, const MultipleDeclarationNode* const parameters, const DynamicNodeCollection* const body) : FixedNodeCollection(base)
    {
        AddChild(ChildCode::Describer, describer);
        AddChild(ChildCode::Type, type);
        AddChild(ChildCode::Parameters, parameters);
        AddChild(ChildCode::Body, body);
    }

    NodeType OperatorOverloadNode::NodeType() const { return NodeType::OperatorOverload; }

    void OperatorOverloadNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Operator Overload Node: " << ToString(token.Kind()) << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Describer))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Type))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Parameters))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Body))->Print(indent + next, true);
    }
}

