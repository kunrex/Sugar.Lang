#ifndef BUILT_IN_BINARY_EXPRESSION_H
#define BUILT_IN_BINARY_EXPRESSION_H

#include "../binary_context_node.h"

namespace Analysis::Structure::Context
{
    class BuiltInBinaryExpression final : public BinaryContextNode
    {
        private:
            mutable int slotCount;
            const Core::Interfaces::IFunction* operation;

        public:
            explicit BuiltInBinaryExpression(const Core::Interfaces::IFunction* operation, const ContextNode* lhs, const ContextNode* rhs);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
