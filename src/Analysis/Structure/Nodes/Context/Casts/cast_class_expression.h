#ifndef CAST_CLASS_EXPRESSION_H
#define CAST_CLASS_EXPRESSION_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class CastClassExpression final : public UnaryContextNode
    {
        private:
            const std::string cilInstruction;

        public:
            explicit CastClassExpression(const Core::DataType* creationType, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
