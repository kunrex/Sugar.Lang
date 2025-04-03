#ifndef NAMEABLE_NODE_H
#define NAMEABLE_NODE_H

#include "../Values/identifier_node.h"

namespace ParseNodes::Core
{
    template <int childCount>
    class NameableNode : public virtual FixedNodeCollection<childCount>
    {
        protected:
            explicit NameableNode(const Values::IdentifierNode* identifier);
    };
}

#endif
