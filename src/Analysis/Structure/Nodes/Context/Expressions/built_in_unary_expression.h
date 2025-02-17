#ifndef BUILT_IN_UNARY_EXPRESSION_H
#define BUILT_IN_UNARY_EXPRESSION_H

#include "../unary_context_node.h"
#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Context
{
    class BuiltInUnaryExpression final : public UnaryContextNode
    {
        private:
            const std::string cilExpression;

        public:
            BuiltInUnaryExpression(const Creation::OverloadDefinition* operation, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;
    };
}

#endif
