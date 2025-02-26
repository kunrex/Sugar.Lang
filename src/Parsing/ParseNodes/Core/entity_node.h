#ifndef ENTITY_NODE_H
#define ENTITY_NODE_H

#include "Interfaces/i_entity_node.h"

namespace ParseNodes::Core
{
    class EntityNode : public virtual Interfaces::IEntityNode
    {
        protected:
            const ParseNode* type;

            explicit EntityNode(const ParseNode* type);

        public:
            [[nodiscard]] const ParseNode* Type() const override;

            ~EntityNode() override;
    };
}

#endif
