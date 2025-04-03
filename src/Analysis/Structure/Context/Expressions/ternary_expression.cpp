#include "ternary_expression.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    TernaryExpression::TernaryExpression(const IDataType* const creationType, const ContextNode* const condition, const ContextNode* const trueValue, const ContextNode* const falseValue) : ContextNode(creationType), condition(condition), trueValue(trueValue), falseValue(falseValue), slotCount(std::max(condition->SlotCount(), std::max(trueValue->SlotCount(), falseValue->SlotCount())))
    { }

    MemberType TernaryExpression::MemberType() const { return MemberType::TernaryExpression; }
    
    int TernaryExpression::SlotCount() const { return slotCount; }

    bool TernaryExpression::Readable() const { return true; }
    bool TernaryExpression::Writable() const { return false; }

    const ContextNode* TernaryExpression::Condition() const { return condition; }

    const ContextNode* TernaryExpression::TrueValue() const { return trueValue; }
 
    const ContextNode* TernaryExpression::FalseValue() const { return falseValue; }

    string TernaryExpression::CILData() const { return ""; }

    TernaryExpression::~TernaryExpression()
    {
        delete condition;
        delete trueValue;
        delete falseValue;
    }
}
