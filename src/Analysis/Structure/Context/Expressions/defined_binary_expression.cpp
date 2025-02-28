#include "defined_binary_expression.h"

#include <format>

#include "../Entities/Functions/function_extensions.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    DefinedBinaryExpression::DefinedBinaryExpression(const IFunction* const operation, const ContextNode* const lhs, const ContextNode* const rhs) : BinaryContextNode(operation->CreationType(), lhs, rhs), slotCount(-1), operation(operation)
    {
        slotCount = std::max(CalculateFunctionCallSlotSize(this), creationType->SlotCount());
    }

    int DefinedBinaryExpression::SlotCount() const { return slotCount; }

    MemberType DefinedBinaryExpression::MemberType() const { return MemberType::BinaryExpression; }

    bool DefinedBinaryExpression::Readable() const { return true; }
    bool DefinedBinaryExpression::Writable() const { return false; }

    string DefinedBinaryExpression::CILInstruction() const { return std::format("call {}", operation->FullName()); }
}

