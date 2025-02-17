#ifndef UNARY_NODE_H
#define UNARY_NODE_H

#include "../operation_expression_node.h"

namespace ParseNodes::Expressions
{
    class UnaryNode final : public OperatorExpressionNode
    {
        private:
            const ParseNode* operand;

        public:
            UnaryNode(const Tokens::Token& base, const ParseNode* operand);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const ParseNode* Operand() const;

            [[nodiscard]] unsigned long Index() const override;

            ~UnaryNode() override;
    };
}

#endif
