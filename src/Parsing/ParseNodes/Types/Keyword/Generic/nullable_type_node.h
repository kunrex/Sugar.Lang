#ifndef NULLABLE_TYPE_NODE_H
#define NULLABLE_TYPE_NODE_H

#include "../../../parse_node.h"

namespace ParseNodes::Types
{
    class NullableTypeNode final : public DynamicNodeCollection
    {
        public:
            explicit NullableTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
