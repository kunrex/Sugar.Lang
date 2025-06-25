#include "function_creation_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Functions::Creation
{
    FunctionCreationNode::FunctionCreationNode(const IParseNode* const describer, const IParseNode* const type, const IParseNode* const identifier, const IParseNode* const parameters, const IParseNode* const body) : FixedNodeCollection(identifier->Token())
    {
        AddChild(ChildCode::Describer, describer);
        AddChild(ChildCode::Type, type);
        AddChild(ChildCode::Identifier, identifier);
        AddChild(ChildCode::Parameters, parameters);
        AddChild(ChildCode::Body, body);
    }

    NodeType FunctionCreationNode::NodeType() const { return NodeType::FunctionDeclaration; }

    void FunctionCreationNode::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Function Creation Node" << std::endl;
        const auto next = last ? " " : "| ";

        GetChild(static_cast<int>(ChildCode::Describer))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Type))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Identifier))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Parameters))->Print(indent + next, false);
        GetChild(static_cast<int>(ChildCode::Body))->Print(indent + next, true);
    }
}
