#ifndef TERNARY_EXPRESSION_H
#define TERNARY_EXPRESSION_H

#include "../context_node.h"

namespace Analysis::Structure::Context
{
    class TernaryExpression : public ContextNode
    {
        protected:
            const ContextNode* condition;
            const ContextNode* trueValue;
            const ContextNode* falseValue;

            mutable int slotCount;

        public:
            TernaryExpression(const Core::Interfaces::IDataType* creationType, const ContextNode* condition, const ContextNode* trueValue, const ContextNode* falseValue);

            [[nodiscard]] Enums::MemberType MemberType() const override;
            
            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;
         
            [[nodiscard]] const ContextNode* Condition() const;
            [[nodiscard]] const ContextNode* TrueValue() const;
            [[nodiscard]] const ContextNode* FalseValue() const;

            [[nodiscard]] std::string CILData() const override;

            ~TernaryExpression() override;
    };
}

#endif 
