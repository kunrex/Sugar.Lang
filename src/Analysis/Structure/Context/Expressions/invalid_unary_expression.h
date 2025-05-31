#ifndef INVALID_UNARY_EXPRESSION_H
#define INVALID_UNARY_EXPRESSION_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class InvalidUnaryExpression final : public UnaryContextNode
    {
        public:
            explicit InvalidUnaryExpression(const IContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
