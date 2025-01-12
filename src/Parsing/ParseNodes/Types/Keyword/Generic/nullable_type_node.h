#ifndef NULLABLE_TYPE_NODE_H
#define NULLABLE_TYPE_NODE_H

#include "generic_type_node.h"

namespace ParseNodes::Types
{
    class NullableTypeNode final : public GenericTypeNode
    {
        public:
            NullableTypeNode(const Tokens::Token& keyword, const Groups::GenericNode* generic);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
