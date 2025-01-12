#ifndef NAMEABLE_NODE_H
#define NAMEABLE_NODE_H

#include "../Values/identifier_node.h"

namespace ParseNodes::Core
{
    class NameableNode
    {
        protected:
            const Values::IdentifierNode* name;

            explicit NameableNode(const Values::IdentifierNode* identifier);

        public:
            [[nodiscard]] const Values::IdentifierNode* Name() const;

            virtual ~NameableNode();
    };
}

#endif
