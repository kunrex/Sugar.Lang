#ifndef ENTITY_NODE_H
#define ENTITY_NODE_H

#include "Interfaces/i_parse_node.h"

namespace ParseNodes::Core
{
    template <int childCount>
    class EntityNode : public virtual FixedNodeCollection<childCount>
    {
        protected:
            explicit EntityNode(const ParseNode* type);
    };
}

#endif
