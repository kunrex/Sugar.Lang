#ifndef DEFINED_UNARY_EXPRESSION_H
#define DEFINED_UNARY_EXPRESSION_H

#include "../unary_context_node.h"

#include "../../Core/Interfaces/Creation/i_function.h"

namespace Analysis::Structure::Context
{
    class DefinedUnaryExpression final : public UnaryContextNode
    {
        private:
            const int slotCount;
            const Core::Interfaces::IFunction* operation;

        public:
            DefinedUnaryExpression(const Core::Interfaces::IFunction* operation, const IContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
