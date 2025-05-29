#include "defined_binary_expression.h"

#include <format>

#include "../Entities/Functions/function_extensions.h"

#include "../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    DefinedBinaryExpression::DefinedBinaryExpression(const IFunction* const operation, const IContextNode* const lhs, const IContextNode* const rhs) : BinaryContextNode(operation->CreationType(), lhs, rhs), slotCount(), operation(operation)
    {
        slotCount = std::max(CalculateFunctionCallSlotSize(this), creationType->SlotCount());
    }

    int DefinedBinaryExpression::SlotCount() const { return slotCount; }

    MemberType DefinedBinaryExpression::MemberType() const { return MemberType::BinaryExpression; }

    bool DefinedBinaryExpression::Readable() const { return true; }
    bool DefinedBinaryExpression::Writable() const { return false; }

    string DefinedBinaryExpression::CILData() const { return operation->MemberType() == MemberType::BuiltInOperation ? operation->FullName() : std::format("call {}", operation->FullName()); }
}

