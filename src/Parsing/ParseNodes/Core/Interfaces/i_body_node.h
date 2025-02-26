#ifndef I_BODY_NODE_H
#define I_BODY_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Core::Interfaces
{
    class IBodyNode
    {
        public:
            [[nodiscard]] virtual const NodeCollection<ParseNode>* Body() const = 0;

            virtual ~IBodyNode() = default;
    };
}

#endif
