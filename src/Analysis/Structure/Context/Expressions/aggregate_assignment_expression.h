#ifndef AGGREGATE_ASSIGNMENT_EXPRESSION_H
#define AGGREGATE_ASSIGNMENT_EXPRESSION_H

#include "../binary_context_node.h"

namespace Analysis::Structure::Context
{
    class AggregateAssignmentExpression final : public BinaryContextNode
    {
        private:
            const int slotCount;

        public:
            AggregateAssignmentExpression(const IContextNode* lhs, const IContextNode* rhs);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;

            ~AggregateAssignmentExpression() override;
    };
}

#endif
