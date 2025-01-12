#ifndef ENTITY_NODE_H
#define ENTITY_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Core
{
    class EntityNode
    {
        protected:
            const ParseNode* type;

            explicit EntityNode(const ParseNode* type);

        public:
            [[nodiscard]] const ParseNode* Type() const;

            virtual ~EntityNode();
    };
}

#endif
