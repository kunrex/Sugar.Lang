#ifndef BUILT_IN_TYPE_H
#define BUILT_IN_TYPE_H

#include "../Keyword/keyword_type_node.h"

namespace ParseNodes::Types
{
    class BuiltInTypeNode final : public KeywordTypeNode
    {
        public:
            explicit BuiltInTypeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
            [[nodiscard]] Tokens::Enums::SyntaxKind Type() const;

            ~BuiltInTypeNode() override;
    };
}

#endif
