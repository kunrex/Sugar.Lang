#ifndef BUILT_IN_UNARY_EXPRESSION_H
#define BUILT_IN_UNARY_EXPRESSION_H

#include "../unary_context_node.h"

#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Context
{
    class BuiltInUnaryExpression final : public UnaryContextNode
    {
        private:
            mutable int slotCount;
            const Core::Interfaces::IFunction* operation;

        public:
            BuiltInUnaryExpression(const Core::Interfaces::IFunction* operation, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] std::string CILInstruction() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;
    };
}

#endif
