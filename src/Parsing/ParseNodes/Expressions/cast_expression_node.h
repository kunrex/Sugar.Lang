#ifndef CAST_EXPRESSION_NODE_H
#define CAST_EXPRESSION_NODE_H

#include "dot_expression_node.h"

namespace ParseNodes::Expressions
{
    class CastExpressionNode final : public DotExpressionNode
    {
        public:
            CastExpressionNode(const ParseNode* lhs, const ParseNode* rhs, const Tokens::Token& as);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
