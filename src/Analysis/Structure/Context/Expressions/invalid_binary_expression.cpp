#include "invalid_binary_expression.h"

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    InvalidBinaryExpression::InvalidBinaryExpression(const ContextNode* const lhs, const ContextNode* const rhs) : BinaryContextNode(rhs->CreationType(), lhs, rhs)
    { }

    MemberType InvalidBinaryExpression::MemberType() const { return MemberType::Invalid; }

    int InvalidBinaryExpression::SlotCount() const { return 0;}

    bool InvalidBinaryExpression::Readable() const { return false; }
    bool InvalidBinaryExpression::Writable() const { return false; }

    string InvalidBinaryExpression::CILInstruction() const { return ""; }
}

