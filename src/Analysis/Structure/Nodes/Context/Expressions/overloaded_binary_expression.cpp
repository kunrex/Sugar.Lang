#include "overloaded_binary_expression.h"

#include "../../../Core/DataTypes/data_type.h"

#include <format>

using namespace Analysis::Structure::Global;

namespace Analysis::Structure::Context
{
    BuiltInBinaryExpression::BuiltInBinaryExpression(const OperatorOverload* operation, const ContextNode* lhs, const ContextNode* rhs) : BinaryContextNode(operation->CreationType(), lhs, rhs), operation(operation)
    { }

    std::string BuiltInBinaryExpression::InstructionGet() const { return std::format("call {} {}{}", creationType->FullName(), operation->FullName(), operation->SignatureString());}
    std::string BuiltInBinaryExpression::InstructionSet() const { return "";}
}

