#ifndef DUPLICATE_EXPRESSION_H
#define DUPLICATE_EXPRESSION_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class DuplicateExpression final : UnaryContextNode
    {
        public:
            explicit DuplicateExpression(const IContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}


#endif
