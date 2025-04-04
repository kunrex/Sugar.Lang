#ifndef CAST_CLASS_EXPRESSION_H
#define CAST_CLASS_EXPRESSION_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class CastClassExpression final : public UnaryContextNode
    {
        private:
            const int slotCount;

        public:
            CastClassExpression(const Core::Interfaces::IDataType* creationType, const IContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
