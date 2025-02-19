#ifndef BUILT_IN_CAST_EXPRESSION_H
#define BUILT_IN_CAST_EXPRESSION_H

#include "../unary_context_node.h"
#include "../../Creation/Functions/cast_definition.h"

namespace Analysis::Structure::Context
{
    class BuiltInCastExpression final : public UnaryContextNode
    {
        private:
            const std::string cilInstruction;

        public:
            explicit BuiltInCastExpression(const Creation::CastDefinition* definition, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
