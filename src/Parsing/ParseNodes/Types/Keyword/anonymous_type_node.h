#ifndef ANONYMOUS_TYPE_H
#define ANONYMOUS_TYPE_H

#include "../../parse_node.h"

namespace ParseNodes::Types
{
    class AnonymousTypeNode final : public ParseNode
    {
        public:
            explicit AnonymousTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}
#endif