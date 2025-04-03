#ifndef INVALID_TERNARY_EXPRESSION_H
#define INVALID_TERNARY_EXPRESSION_H

#include "ternary_expression.h"

namespace Analysis::Structure::Context
{
    class InvalidTernaryExpression final : public TernaryExpression
    {
        public:
            InvalidTernaryExpression(const ContextNode* condition, const ContextNode* trueValue, const ContextNode* falseValue);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;
    };
}


#endif
