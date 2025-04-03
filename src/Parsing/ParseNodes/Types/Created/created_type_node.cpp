#include "created_type_node.h"

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;

namespace ParseNodes::Types
{
    CreatedTypeNode::CreatedTypeNode(const IdentifierNode* const identifier) : ParseNode(identifier->Token())
    {
        children.push_back(identifier);
    }

    NodeType CreatedTypeNode::NodeType() const { return NodeType::CreatedType;}
}