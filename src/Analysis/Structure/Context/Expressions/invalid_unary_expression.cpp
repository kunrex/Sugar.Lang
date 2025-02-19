#include "invalid_unary_expression.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    InvalidUnaryExpression::InvalidUnaryExpression(const ContextNode* operand) : UnaryContextNode(operand->CreationType(), operand)
    { }

    MemberType InvalidUnaryExpression::MemberType() const { return MemberType::Invalid; }

    bool InvalidUnaryExpression::Readable() const { return false; }
    bool InvalidUnaryExpression::Writable() const { return false; }

    std::string InvalidUnaryExpression::InstructionGet() const { return ""; }
    std::string InvalidUnaryExpression::InstructionSet() const { return ""; }
}
