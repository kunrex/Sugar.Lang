#ifndef I_DESCRIBABLE_NODE_H
#define I_DESCRIBABLE_NODE_H

#include "../../Describers/describer_node.h"

namespace ParseNodes::Core::Interfaces
{
    class IDescribableNode
    {
        public:
            [[nodiscard]] virtual const Describers::DescriberNode* Describer() const = 0;

            virtual ~IDescribableNode() = default;
    };
}

#endif
