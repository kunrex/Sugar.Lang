#ifndef BUILT_IN_BINARY_EXPRESSION_H
#define BUILT_IN_BINARY_EXPRESSION_H

#include "../binary_context_node.h"
#include "../../Global/BuiltIn/built_in_operation.h"

namespace Analysis::Structure::Context
{
    class BuiltInBinaryExpression final : public BinaryContextNode
    {
        private:
            const std::string cilExpression;

        public:
            explicit BuiltInBinaryExpression(const Creation::OverloadDefinition* operation, const ContextNode* lhs, const ContextNode* rhs);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
