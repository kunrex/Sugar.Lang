#ifndef VOID_TYPE_H
#define VOID_TYPE_H

#include "../../parse_node.h"

namespace ParseNodes::Types
{
    class VoidTypeNode final : public ParseNode
    {
        public:
            explicit VoidTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif