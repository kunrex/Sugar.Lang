#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include "../operation_expression_node.h"

namespace ParseNodes::Expressions
{
    class BinaryNode final : public OperatorExpressionNode
    {
        private:
            const ParseNode* lhs;
            const ParseNode* rhs;

        public:
            BinaryNode(const Tokens::Token& base, const ParseNode* lhs, const ParseNode* rhs);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const ParseNode* LHS() const;
            [[nodiscard]] const ParseNode* RHS() const;

            ~BinaryNode() override;
    };
}

#endif
