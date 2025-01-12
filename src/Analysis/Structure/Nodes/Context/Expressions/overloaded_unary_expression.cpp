#include "overloaded_unary_expression.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Global;

namespace Analysis::Structure::Context
{
    OverloadedUnaryExpression::OverloadedUnaryExpression(const OperatorOverload* operation, const ContextNode* operand) : UnaryContextNode(operation->CreationType(), operand), operation(operation)
    { }

    std::string OverloadedUnaryExpression::InstructionGet() const { return std::format("call {} {}{}", creationType->FullName(), operation->FullName(), operation->SignatureString());}
    std::string OverloadedUnaryExpression::InstructionSet() const { return ""; }
}

