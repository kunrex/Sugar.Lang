#include "entity_node.h"

#include "characteristic_node.h"

namespace ParseNodes::Core
{
    EntityNode::EntityNode(const ParseNode* const type) : type(type)
    { }

    const ParseNode* EntityNode::Type() const { return type; }

    EntityNode::~EntityNode()
    {
        delete type;
    }
}
