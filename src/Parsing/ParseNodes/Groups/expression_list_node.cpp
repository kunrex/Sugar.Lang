#include "expression_list_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    CompoundDeclarationNode::CompoundDeclarationNode() : NodeCollection()
    { }

    NodeType CompoundDeclarationNode::NodeType() const { return NodeType::CompoundCreation; }
}
