#ifndef CREATED_TYPE_H
#define CREATED_TYPE_H

#include "../../Values/identifier_node.h"

namespace ParseNodes::Types
{
    class CreatedTypeNode final : public ParseNode
    {
        private:
            const Values::IdentifierNode* identifier;

        public:
            explicit CreatedTypeNode(const Values::IdentifierNode* identifier);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const Values::IdentifierNode* Identifier() const;
            [[nodiscard]] unsigned long Index() const override;

            ~CreatedTypeNode() override;
    };
}

#endif
