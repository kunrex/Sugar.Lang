#ifndef DEFINED_BINARY_EXPRESSION_H
#define DEFINED_BINARY_EXPRESSION_H

#include "../binary_context_node.h"
#include "../../Creation/Functions/overload_definition.h"

namespace Analysis::Structure::Context
{
    class DefinedBinaryExpression final : public BinaryContextNode
    {
        private:
            mutable int slotCount;
            const Core::Interfaces::IFunction* operation;

        public:
            DefinedBinaryExpression(const Core::Interfaces::IFunction* operation, const IContextNode* lhs, const IContextNode* rhs);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
