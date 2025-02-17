#ifndef DEFINED_UNARY_EXPRESSION_H
#define DEFINED_UNARY_EXPRESSION_H

#include "../unary_context_node.h"
#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Context
{
    class DefinedUnaryExpression final : public UnaryContextNode
    {
        private:
            const std::string cilExpression;

        public:
            DefinedUnaryExpression(const Creation::OverloadDefinition* operation, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
