#ifndef CAST_CLASS_EXPRESSION_H
#define CAST_CLASS_EXPRESSION_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class CastClassExpression final : public UnaryContextNode
    {
        private:
            mutable int slotCount;

        public:
            explicit CastClassExpression(const Core::Interfaces::IDataType* creationType, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILInstruction() const override;
    };
}

#endif
