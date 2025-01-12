#ifndef OPERATION_EXPRESSION_NODE_H
#define OPERATION_EXPRESSION_NODE_H

#include "../parse_node.h"
#include "../../../Lexing/Tokens/token.h"

namespace ParseNodes::Expressions
{
    class OperatorExpressionNode : public ParseNode
    {
        protected:
            const Tokens::Token& base;

            explicit OperatorExpressionNode(const Tokens::Token& base);

        public:
            [[nodiscard]] const Tokens::Token& Base() const;
    };
}

#endif
