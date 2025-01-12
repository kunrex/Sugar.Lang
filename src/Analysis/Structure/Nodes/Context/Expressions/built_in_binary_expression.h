#ifndef BUILT_IN_BINARY_EXPRESSION_H
#define BUILT_IN_BINARY_EXPRESSION_H

#include "../binary_context_node.h"
#include "../../Global/BuiltIn/built_in_operation.h"

namespace Analysis::Structure::Context
{
    class BuiltInBinaryExpression final : public BinaryContextNode
    {
        private:
            const Global::BuiltInOperation* operation;

        public:
            explicit BuiltInBinaryExpression(const Global::BuiltInOperation* operation, const ContextNode* lhs, const ContextNode* rhs);

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
