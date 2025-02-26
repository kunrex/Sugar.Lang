#ifndef I_ENTITY_NODE_H
#define I_ENTITY_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Core::Interfaces
{
    class IEntityNode
    {
        public:
            [[nodiscard]] virtual const ParseNode* Type() const = 0;

            virtual ~IEntityNode() = default;
    };
}

#endif
