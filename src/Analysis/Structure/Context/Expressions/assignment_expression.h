#ifndef ASSIGNMENT_EXPRESSION_H
#define ASSIGNMENT_EXPRESSION_H

#include "../binary_context_node.h"

namespace Analysis::Structure::Context
{
    class AssignmentExpression final : public BinaryContextNode
    {
        private:
            const int slotCount;

        public:
            AssignmentExpression(const IContextNode* lhs, const IContextNode* rhs);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
    };
}

#endif
