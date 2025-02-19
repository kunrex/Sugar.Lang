#include "cast_class_expression.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Context
{
    CastClassExpression::CastClassExpression(const DataType* creationType, const ContextNode* operand) : UnaryContextNode(creationType, operand), cilInstruction(std::format("castclass {}", creationType->FullName()))
    {
        slotCount = std::max(operand->CreationType()->SlotCount(), creationType->SlotCount());
    }

    MemberType CastClassExpression::MemberType() const { return MemberType::CastClass; }

    bool CastClassExpression::Readable() const { return true; }
    bool CastClassExpression::Writable() const { return false; }

    std::string CastClassExpression::InstructionGet() const { return cilInstruction; }
    std::string CastClassExpression::InstructionSet() const { return ""; }
}
