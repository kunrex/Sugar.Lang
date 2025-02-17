#ifndef CONSTANT_NODE_H
#define CONSTANT_NODE_H

#include "../../../Lexing/Tokens/token.h"

#include "../parse_node.h"

namespace ParseNodes::Constants
{
    class ConstantNode final : public ParseNode
    {
        private:
            const Tokens::Token& token;

        public:
            explicit ConstantNode(const Tokens::Token& token);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] Tokens::Enums::TypeKind ConstantType() const;

            template <typename TType>
            [[nodiscard]] std::optional<TType> Value() const;

            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
