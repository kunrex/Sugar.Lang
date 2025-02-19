#include "invalid_indexer_expression.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    InvalidIndexerExpression::InvalidIndexerExpression(const ContextNode* operand) : UnaryContextNode(operand->CreationType(), operand)
    { }

    MemberType InvalidIndexerExpression::MemberType() const { return MemberType::Invalid; }

    bool InvalidIndexerExpression::Readable() const { return false; }
    bool InvalidIndexerExpression::Writable() const { return false; }

    std::string InvalidIndexerExpression::InstructionGet() const { return ""; }
    std::string InvalidIndexerExpression::InstructionSet() const { return ""; }
}

