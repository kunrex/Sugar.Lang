#ifndef CONSTANT_NODE_H
#define CONSTANT_NODE_H

#include "../parse_node.h"
#include "../../../Lexing/Tokens/token.h"

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
    };
}

#endif
