#include "overloaded_cast_instruction.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    OverloadedCastInstruction::OverloadedCastInstruction(const CastDefinition* definition, const ContextNode* operand) : UnaryContextNode(definition->CreationType(), operand), definition(definition)
    { }

    int OverloadedCastInstruction::SlotCount() const { return std::max(definition->CreationType()->SlotCount(), operand->CreationType()->SlotCount()); }

    std::string OverloadedCastInstruction::InstructionGet() const { return std::format("call {} {}{}", definition->CreationType()->FullName(), definition->FullName(), definition->SignatureString()); }
    std::string OverloadedCastInstruction::InstructionSet() const { return ""; }
}
