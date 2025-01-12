#ifndef LIST_TYPE_NODE_H
#define LIST_TYPE_NODE_H

#include "generic_type_node.h"

namespace ParseNodes::Types
{
    class ListTypeNode final : public GenericTypeNode
    {
        public:
            ListTypeNode(const Tokens::Token& keyword, const Groups::GenericNode* generic);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
