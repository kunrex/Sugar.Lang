#ifndef CREATED_TYPE_H
#define CREATED_TYPE_H

#include "../../Values/identifier_node.h"

namespace ParseNodes::Types
{
    class CreatedTypeNode final : public ParseNode
    {
        public:
            explicit CreatedTypeNode(const Values::IdentifierNode* identifier);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
