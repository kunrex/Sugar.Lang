#ifndef UNBOX_CAST_INSTRUCTION_H
#define UNBOX_CAST_INSTRUCTION_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class UnboxCastExpression final : public UnaryContextNode
    {
        private:
            mutable int slotCount;

        public:
            UnboxCastExpression(const Core::Interfaces::IDataType* creationType, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILInstruction() const override;
    };
}

#endif
