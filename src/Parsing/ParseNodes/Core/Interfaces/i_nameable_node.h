#ifndef I_NAMEABLE_NODE_H
#define I_NAMEABLE_NODE_H

#include "../../Values/identifier_node.h"

namespace ParseNodes::Core::Interfaces
{
    class INameableNode
    {
        public:
            [[nodiscard]] virtual const Values::IdentifierNode* Name() const = 0;

            virtual ~INameableNode() = default;
    };
}


#endif
