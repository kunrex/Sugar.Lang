#ifndef STATEMENT_NODE_H
#define STATEMENT_NODE_H

#include "../parse_node.h"
#include "../../../Lexing/Tokens/token.h"

namespace ParseNodes::Statements
{
    class StatementNode : public ParseNode
    {
        private:
            const Tokens::Token& separator;

        protected:
            explicit StatementNode(const Tokens::Token& separator);

        public:
            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
