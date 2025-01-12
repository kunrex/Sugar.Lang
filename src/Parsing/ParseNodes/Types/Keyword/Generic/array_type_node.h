#ifndef ARRAY_TYPE_H
#define ARRAY_TYPE_H

#include "generic_type_node.h"

namespace ParseNodes::Types
{
    class ArrayTypeNode final : public GenericTypeNode
    {
        public:
            ArrayTypeNode(const Tokens::Token& keyword, const Groups::GenericNode* generic);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
