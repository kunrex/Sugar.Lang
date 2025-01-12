#ifndef OVERLOADED_UNARY_EXPRESSION_H
#define OVERLOADED_UNARY_EXPRESSION_H

#include "../unary_context_node.h"
#include "../../Global/UserDefined/operator_overload.h"

namespace Analysis::Structure::Context
{
    class OverloadedUnaryExpression final : public UnaryContextNode
    {
        private:
            const Global::OperatorOverload* operation;

        public:
            OverloadedUnaryExpression(const Global::OperatorOverload* operation, const ContextNode* operand);

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
