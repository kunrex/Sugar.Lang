#include "ternary_expression.h"

using namespace std;

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    TernaryExpression::TernaryExpression(const IDataType* const creationType, const IContextNode* const condition, const IContextNode* const trueValue, const IContextNode* const falseValue) : FixedContextCollection(creationType), slotCount(std::max(condition->SlotCount(), std::max(trueValue->SlotCount(), falseValue->SlotCount())))
    {
        AddChild(ChildCode::Expression, condition);
        AddChild(ChildCode::LHS, trueValue);
        AddChild(ChildCode::RHS, falseValue);
    }

    MemberType TernaryExpression::MemberType() const { return MemberType::TernaryExpression; }
    
    int TernaryExpression::SlotCount() const { return slotCount; }

    bool TernaryExpression::Readable() const { return true; }
    bool TernaryExpression::Writable() const { return false; }

    std::string TernaryExpression::CILData() const { return ""; }
}
