#include "built_in_binary_expression.h"

#include "../Entities/Functions/function_extensions.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    BuiltInBinaryExpression::BuiltInBinaryExpression(const IFunction* const operation, const ContextNode* const lhs, const ContextNode* const rhs) : BinaryContextNode(operation->CreationType(), lhs, rhs), operation(operation)
    {
        slotCount = std::max(CalculateFunctionCallSlotSize(this), creationType->SlotCount());
    }

    MemberType BuiltInBinaryExpression::MemberType() const { return MemberType::BinaryExpression; }

    int BuiltInBinaryExpression::SlotCount() const { return slotCount; }

    bool BuiltInBinaryExpression::Readable() const { return true; }
    bool BuiltInBinaryExpression::Writable() const { return false; }

    std::string BuiltInBinaryExpression::CILInstruction() const { return operation->FullName(); }
}
