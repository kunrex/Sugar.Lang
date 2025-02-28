#include "invalid_cast_expression.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    InvalidCastExpression::InvalidCastExpression(const IDataType* const creationType, const ContextNode* const operand) : UnaryContextNode(creationType, operand)
    { }

    MemberType InvalidCastExpression::MemberType() const { return MemberType::Invalid; }

    int InvalidCastExpression::SlotCount() const { return 0; }

    bool InvalidCastExpression::Readable() const { return false; }
    bool InvalidCastExpression::Writable() const { return false; }

    string InvalidCastExpression::CILInstruction() const { return ""; }
}
