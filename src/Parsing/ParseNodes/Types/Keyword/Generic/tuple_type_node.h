#ifndef TUPLE_TYPE_NODE_H
#define TUPLE_TYPE_NODE_H

#include "generic_type_node.h"

namespace ParseNodes::Types
{
    class TupleTypeNode final : public GenericTypeNode
    {
        public:
            TupleTypeNode(const Tokens::Token& keyword, const Groups::GenericNode* generic);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
