#ifndef ACTION_TYPE_H
#define ACTION_TYPE_H

#include "generic_type_node.h"

namespace ParseNodes::Types
{
    class ActionTypeNode final : public GenericTypeNode
    {
        public:
            ActionTypeNode(const Tokens::Token& keyword, const Groups::GenericNode* generic);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
