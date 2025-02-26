#ifndef NAMEABLE_NODE_H
#define NAMEABLE_NODE_H

#include "Interfaces/i_nameable_node.h"

namespace ParseNodes::Core
{
    class NameableNode : public virtual Interfaces::INameableNode
    {
        protected:
            const Values::IdentifierNode* name;

            explicit NameableNode(const Values::IdentifierNode* identifier);

        public:
            [[nodiscard]] const Values::IdentifierNode* Name() const override;

            ~NameableNode() override;
    };
}

#endif
