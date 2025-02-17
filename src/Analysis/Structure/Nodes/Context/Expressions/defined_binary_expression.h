#ifndef DEFINED_BINARY_EXPRESSION_H
#define DEFINED_BINARY_EXPRESSION_H

#include "../binary_context_node.h"
#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Context
{
    class DefinedBinaryExpression final : public BinaryContextNode
    {
        private:
            const std::string cilExpression;

        public:
            explicit DefinedBinaryExpression(const Creation::OverloadDefinition* operation, const ContextNode* lhs, const ContextNode* rhs);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;

            [[nodiscard]] int SlotCount() const override;
    };
}

#endif
