
#ifndef OVERLOADED_BINARY_EXPRESSION_H
#define OVERLOADED_BINARY_EXPRESSION_H

#include "../binary_context_node.h"
#include "../../Global/UserDefined/operator_overload.h"

namespace Analysis::Structure::Context
{
    class BuiltInBinaryExpression final : public BinaryContextNode
    {
        private:
            const Global::OperatorOverload* operation;

        public:
            explicit BuiltInBinaryExpression(const Global::OperatorOverload* operation, const ContextNode* lhs, const ContextNode* rhs);

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif //OVERLOADED_BINARY_EXPRESSION_H
