#ifndef DESCRIBABLE_NODE_H
#define DESCRIBABLE_NODE_H

#include "../Describers/describer_node.h"

namespace ParseNodes::Core
{
    template <int childCount>
    class DescribableNode : public virtual FixedNodeCollection<childCount>
    {
        protected:
            explicit DescribableNode(const Describers::DescriberNode* describer);
    };
}


#endif
