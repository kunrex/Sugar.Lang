#include "invalid_ternary_expression.h"

#include "../../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    InvalidTernaryExpression::InvalidTernaryExpression(const ContextNode* const condition, const ContextNode* const trueValue, const ContextNode* const falseValue) : TernaryExpression(&Object::Instance(), condition, trueValue, falseValue)
    { }

    MemberType InvalidTernaryExpression::MemberType() const { return MemberType::Invalid; }

    int InvalidTernaryExpression::SlotCount() const { return 0; }
}
