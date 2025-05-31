#ifndef TERNARY_EXPRESSION_H
#define TERNARY_EXPRESSION_H

#include "../context_node.h"

namespace Analysis::Structure::Context
{
    class TernaryExpression : public FixedContextCollection<3>
    {
        protected:
            const int slotCount;

        public:
            TernaryExpression(const Core::Interfaces::IDataType* creationType, const IContextNode* condition, const IContextNode* trueValue, const IContextNode* falseValue);

            [[nodiscard]] Enums::MemberType MemberType() const override;
            
            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif 
