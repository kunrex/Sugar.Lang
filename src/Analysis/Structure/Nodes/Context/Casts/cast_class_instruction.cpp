#include "cast_class_instruction.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Context
{
    CastClassInstruction::CastClassInstruction(const DataType* creationType, const ContextNode* operand) : UnaryContextNode(creationType, operand)
    { }

    int CastClassInstruction::SlotCount() const { return std::max(operand->CreationType()->SlotCount(), creationType->SlotCount()); }

    std::string CastClassInstruction::InstructionGet() const { return std::format("castclass {}", creationType->FullName());}
    std::string CastClassInstruction::InstructionSet() const { return ""; }
}
