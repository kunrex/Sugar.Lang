#include "defined_cast_expression.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    DefinedCastExpression::DefinedCastExpression(const CastDefinition* definition, const ContextNode* operand) : UnaryContextNode(definition->CreationType(), operand), cilInstruction(std::format("call {}", definition->SignatureString()))
    {
        slotCount = std::max(definition->CreationType()->SlotCount(), operand->CreationType()->SlotCount());
    }

    MemberType DefinedCastExpression::MemberType() const { return MemberType::DefinedCast; }

    bool DefinedCastExpression::Readable() const { return true; }
    bool DefinedCastExpression::Writable() const { return false; }

    std::string DefinedCastExpression::InstructionGet() const { return cilInstruction; }
    std::string DefinedCastExpression::InstructionSet() const { return ""; }
}
