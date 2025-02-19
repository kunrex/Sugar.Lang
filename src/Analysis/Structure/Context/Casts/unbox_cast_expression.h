#ifndef UNBOX_CAST_INSTRUCTION_H
#define UNBOX_CAST_INSTRUCTION_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class UnboxCastExpression final : public UnaryContextNode
    {
        private:
            const std::string cilInstruction;

        public:
            UnboxCastExpression(const Core::DataType* creationType, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
