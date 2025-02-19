#include "invalid_binary_expression.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    InvalidBinaryExpression::InvalidBinaryExpression(const ContextNode* lhs, const ContextNode* rhs) : BinaryContextNode(rhs->CreationType(), lhs, rhs)
    { }

    MemberType InvalidBinaryExpression::MemberType() const { return MemberType::Invalid; }

    bool InvalidBinaryExpression::Readable() const { return false; }
    bool InvalidBinaryExpression::Writable() const { return false; }

    std::string InvalidBinaryExpression::InstructionGet() const { return ""; }
    std::string InvalidBinaryExpression::InstructionSet() const { return ""; }
}

