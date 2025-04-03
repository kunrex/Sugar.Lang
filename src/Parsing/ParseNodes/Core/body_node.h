#ifndef BODY_NODE
#define BODY_NODE

#include "../parse_node.h"

namespace ParseNodes::Core
{
    template <int childCount>
    class BodyNode : public virtual FixedNodeCollection<childCount>
    {
        protected:
            explicit BodyNode(const DynamicNodeCollection* body);
    };
}

#endif
