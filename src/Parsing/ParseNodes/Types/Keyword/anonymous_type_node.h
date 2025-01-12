#ifndef ANONYMOUS_TYPE_H
#define ANONYMOUS_TYPE_H

#include "keyword_type_node.h"

namespace ParseNodes::Types
{
    class AnonymousTypeNode final : public KeywordTypeNode
    {
        public:
            explicit AnonymousTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}
#endif
