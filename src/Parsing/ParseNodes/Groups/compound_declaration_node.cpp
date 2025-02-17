#include "compound_declaration_node.h"

using namespace ParseNodes::Enums;

namespace ParseNodes::Groups
{
    CompoundDeclarationNode::CompoundDeclarationNode() : NodeCollection()
    { }

    NodeType CompoundDeclarationNode::NodeType() const { return NodeType::CompoundCreation; }

    unsigned long CompoundDeclarationNode::Index() const
    {
        if (!children.empty())
            return children[0]->Index();

        return 0;
    }
}
