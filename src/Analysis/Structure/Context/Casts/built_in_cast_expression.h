#ifndef BUILT_IN_CAST_EXPRESSION_H
#define BUILT_IN_CAST_EXPRESSION_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class BuiltInCastExpression final : public UnaryContextNode
    {
        private:
            mutable int slotCount;
            const Core::Interfaces::IFunction* definition;

        public:
            BuiltInCastExpression(const Core::Interfaces::IFunction* definition, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
