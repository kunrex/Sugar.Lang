#ifndef DEFINED_CAST_EXPRESSION_H
#define DEFINED_CAST_EXPRESSION_H

#include "../unary_context_node.h"

#include "../../Core/Interfaces/Creation/i_function.h"

namespace Analysis::Structure::Context
{
    class DefinedCastExpression final : public UnaryContextNode
    {
        private:
            mutable int slotCount;
            const Core::Interfaces::IFunction* definition;

        public:
            DefinedCastExpression(const Core::Interfaces::IFunction* definition, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
