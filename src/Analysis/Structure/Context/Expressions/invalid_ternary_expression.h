#ifndef INVALID_TERNARY_EXPRESSION_H
#define INVALID_TERNARY_EXPRESSION_H

#include "ternary_expression.h"

namespace Analysis::Structure::Context
{
    class InvalidTernaryExpression final : public TernaryExpression
    {
        public:
            InvalidTernaryExpression(const IContextNode* condition, const IContextNode* trueValue, const IContextNode* falseValue);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}


#endif
