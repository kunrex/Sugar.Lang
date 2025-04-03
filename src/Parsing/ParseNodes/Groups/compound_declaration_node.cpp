#include "compound_declaration_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    CompoundDeclarationNode::CompoundDeclarationNode(const Tokens::Token& token) : DynamicNodeCollection(token)
    { }

    NodeType CompoundDeclarationNode::NodeType() const { return NodeType::CompoundDeclaration; }
}
