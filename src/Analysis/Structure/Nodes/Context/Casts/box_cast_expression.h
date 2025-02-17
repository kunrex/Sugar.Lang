#ifndef BOX_CAST_EXPRESSION_H
#define BOX_CAST_EXPRESSION_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class BoxCastExpression final : public UnaryContextNode
    {
        private:
            const std::string cilInstruction;

        public:
            explicit BoxCastExpression(const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
