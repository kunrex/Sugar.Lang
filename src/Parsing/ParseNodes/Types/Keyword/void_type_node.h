#ifndef VOID_TYPE_H
#define VOID_TYPE_H

#include "keyword_type_node.h"

namespace ParseNodes::Types
{
    class VoidTypeNode final : public KeywordTypeNode
    {
        public:
            explicit VoidTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
