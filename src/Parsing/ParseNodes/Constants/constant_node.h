#ifndef CONSTANT_NODE_H
#define CONSTANT_NODE_H

#include "../../../Lexing/Tokens/token.h"

#include "../parse_node.h"

namespace ParseNodes::Constants
{
    class ConstantNode final : public ParseNode
    {
        public:
            explicit ConstantNode(const Tokens::Token& token);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
