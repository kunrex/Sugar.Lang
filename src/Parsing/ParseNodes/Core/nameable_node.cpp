#include "nameable_node.h"

using namespace ParseNodes::Values;

namespace ParseNodes::Core
{
    NameableNode::NameableNode(const IdentifierNode* identifier) : name(identifier)
    { }

    const IdentifierNode* NameableNode::Name() const { return name; }

    NameableNode::~NameableNode()
    {
        delete name;
    }
}
