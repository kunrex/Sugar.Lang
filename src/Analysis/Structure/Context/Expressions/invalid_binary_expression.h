#ifndef INVALID_BINARY_EXPRESSION_H
#define INVALID_BINARY_EXPRESSION_H

#include "../binary_context_node.h"

namespace Analysis::Structure::Context
{
    class InvalidBinaryExpression final : public BinaryContextNode
    {
        public:
            explicit InvalidBinaryExpression(const ContextNode* lhs, const ContextNode* rhs);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif