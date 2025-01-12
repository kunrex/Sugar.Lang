#ifndef FUNC_TYPE_H
#define FUNC_TYPE_H

#include "generic_type_node.h"

namespace ParseNodes::Types
{
    class FuncTypeNode final : public GenericTypeNode
    {
        public:
            FuncTypeNode(const Tokens::Token& keyword, const Groups::GenericNode* generic);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
