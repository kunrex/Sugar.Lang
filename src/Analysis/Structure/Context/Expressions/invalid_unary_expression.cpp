#include "invalid_unary_expression.h"

#include <iostream>

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    InvalidUnaryExpression::InvalidUnaryExpression(const IContextNode* const operand) : UnaryContextNode(operand->CreationType(), operand)
    { }

    MemberType InvalidUnaryExpression::MemberType() const { return MemberType::Invalid; }

    int InvalidUnaryExpression::SlotCount() const { return 0; }

    bool InvalidUnaryExpression::Readable() const { return false; }
    bool InvalidUnaryExpression::Writable() const { return false; }

    string InvalidUnaryExpression::CILData() const { return ""; }

    void InvalidUnaryExpression::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Invalid Unary Expression" << std::endl;
        FixedContextCollection::Print(indent, last);
    }
}
