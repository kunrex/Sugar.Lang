#ifndef THROW_STATEMENT_NODE_H
#define THROW_STATEMENT_NODE_H

#include "statement_node.h"

namespace ParseNodes::Statements
{
    class ThrowStatementNode final : public StatementNode
    {
        private:
            const ParseNode* exception;

            const Tokens::Token& keyword;

        public:
            ThrowStatementNode(const ParseNode* exception, const Tokens::Token& keyword, const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const ParseNode* Exception() const;

            [[nodiscard]] unsigned long Index() const override;

            ~ThrowStatementNode() override;
    };
}

#endif
