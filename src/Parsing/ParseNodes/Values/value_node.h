#ifndef VALUE_NODE_H
#define VALUE_NODE_H

#include "../../../Lexing/Tokens/token.h"

#include "../parse_node.h"

namespace ParseNodes::Values
{
    class ValueNode : public ParseNode
    {
        protected:
            const Tokens::Token& token;

            explicit ValueNode(const Tokens::Token& token);

        public:
            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
