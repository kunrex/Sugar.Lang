#ifndef PROPERTY_NODE_H
#define PROPERTY_NODE_H

#include "../Properties/Accessors/get_node.h"
#include "../Properties/Accessors/set_node.h"

namespace ParseNodes::Core
{
    template <int childCount>
    class PropertyNode : public virtual FixedNodeCollection<childCount>
    {
        protected:
            PropertyNode(const Properties::GetNode* get, const Properties::SetNode* set);
    };
}

#endif
