#ifndef EXPRESSION_STATEMENT_NODE_H
#define EXPRESSION_STATEMENT_NODE_H

#include "statement_node.h"

namespace ParseNodes::Statements
{
    class ExpressionStatementNode final : public StatementNode
    {
        private:
            const ParseNode* expression;

        public:
            ExpressionStatementNode(const ParseNode* expression, const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const ParseNode* Expression() const;

            ~ExpressionStatementNode() override;
    };
}

#endif
