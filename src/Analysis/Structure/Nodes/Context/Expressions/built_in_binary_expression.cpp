#include "built_in_binary_expression.h"

using namespace Analysis::Structure::Global;

namespace Analysis::Structure::Context
{
    BuiltInBinaryExpression::BuiltInBinaryExpression(const BuiltInOperation* operation, const ContextNode* lhs, const ContextNode* rhs) : BinaryContextNode(operation->CreationType(), lhs, rhs), operation(operation)
    { }

    std::string BuiltInBinaryExpression::InstructionGet() const { return operation->Instruction(); }
    std::string BuiltInBinaryExpression::InstructionSet() const { return "";}
}
