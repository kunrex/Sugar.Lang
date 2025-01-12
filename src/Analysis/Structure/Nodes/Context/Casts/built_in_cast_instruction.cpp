#include "built_in_cast_instruction.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Global;

namespace Analysis::Structure::Context
{
    BuiltInCastInstruction::BuiltInCastInstruction(const BuiltInCast* definition, const ContextNode* operand) : UnaryContextNode(definition->CreationType(), operand), definition(definition)
    { }

    int BuiltInCastInstruction::SlotCount() const { return std::max(definition->CreationType()->SlotCount(), operand->CreationType()->SlotCount()); }

    std::string BuiltInCastInstruction::InstructionGet() const { return definition->Instruction(); }
    std::string BuiltInCastInstruction::InstructionSet() const { return ""; }
}
