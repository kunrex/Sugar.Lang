#include "dot_expression.h"

namespace Analysis::Structure::Context
{
    DotExpression::DotExpression(const ContextNode* lhs, const ContextNode* rhs) : BinaryContextNode(rhs->CreationType(),lhs, rhs)
    { }

    [[nodiscard]] std::string DotExpression::InstructionGet() const { return ""; }
    [[nodiscard]] std::string DotExpression::InstructionSet() const { return ""; }
}
