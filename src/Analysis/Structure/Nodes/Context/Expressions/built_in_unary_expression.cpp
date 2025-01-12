#include "built_in_unary_expression.h"

using namespace Analysis::Structure::Global;

namespace Analysis::Structure::Context
{
    BuiltInUnaryExpression::BuiltInUnaryExpression(const BuiltInOperation* operation, const ContextNode* operand) : UnaryContextNode(operation->CreationType(), operand), operation(operation)
    { }

    std::string BuiltInUnaryExpression::InstructionGet() const { return operation->Instruction();}
    std::string BuiltInUnaryExpression::InstructionSet() const { return ""; }
}
