#include "created_type_node.h"

using namespace ParseNodes::Enums;
using namespace ParseNodes::Values;

namespace ParseNodes::Types
{
    CreatedTypeNode::CreatedTypeNode(const IdentifierNode* const identifier) : ParseNode(), identifier(identifier)
    { }

    NodeType CreatedTypeNode::NodeType() const { return NodeType::CreatedType;}

    const IdentifierNode* CreatedTypeNode::Identifier() const { return identifier; }
    unsigned long CreatedTypeNode::Index() const { return identifier->Index(); }

    CreatedTypeNode::~CreatedTypeNode()
    {
        delete identifier;
    }
}
