#ifndef BUILT_IN_UNARY_EXPRESSION_H
#define BUILT_IN_UNARY_EXPRESSION_H

#include "../unary_context_node.h"
#include "../../Global/BuiltIn/built_in_operation.h"

namespace Analysis::Structure::Context
{
    class BuiltInUnaryExpression final : public UnaryContextNode
    {
        private:
            const Global::BuiltInOperation* operation;

        public:
            BuiltInUnaryExpression(const Global::BuiltInOperation* operation, const ContextNode* operand);

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
