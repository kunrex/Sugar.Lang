#include "invalid_binary_expression.h"

#include <iostream>

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    InvalidBinaryExpression::InvalidBinaryExpression(const IContextNode* const lhs, const IContextNode* const rhs) : BinaryContextNode(rhs->CreationType(), lhs, rhs)
    { }

    MemberType InvalidBinaryExpression::MemberType() const { return MemberType::Invalid; }

    int InvalidBinaryExpression::SlotCount() const { return 0;}

    bool InvalidBinaryExpression::Readable() const { return false; }
    bool InvalidBinaryExpression::Writable() const { return false; }

    std::string InvalidBinaryExpression::CILData() const { return ""; }

    void InvalidBinaryExpression::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Invalid Binary Expression" << std::endl;
        FixedContextCollection::Print(indent, last);
    }
}

