#include "defined_binary_expression.h"

#include "../../../Core/DataTypes/data_type.h"

#include <format>

#include "defined_unary_expression.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    DefinedBinaryExpression::DefinedBinaryExpression(const OverloadDefinition* operation, const ContextNode* lhs, const ContextNode* rhs) : BinaryContextNode(operation->CreationType(), lhs, rhs), cilExpression(std::format("call {}", operation->SignatureString()))
    {
        slotCount = std::max(operation->CreationType()->SlotCount(), std::max(lhs->SlotCount(), rhs->SlotCount()));
    }

    MemberType DefinedBinaryExpression::MemberType() const { return MemberType::BinaryExpression; }

    bool DefinedBinaryExpression::Readable() const { return true; }
    bool DefinedBinaryExpression::Writable() const { return false; }

    std::string DefinedBinaryExpression::InstructionGet() const { return cilExpression; }
    std::string DefinedBinaryExpression::InstructionSet() const { return "";}

    int DefinedBinaryExpression::SlotCount() const
    {
        return slotCount;
    }
}

