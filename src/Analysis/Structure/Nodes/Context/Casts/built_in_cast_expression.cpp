#include "built_in_cast_expression.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    BuiltInCastExpression::BuiltInCastExpression(const CastDefinition* definition, const ContextNode* operand) : UnaryContextNode(definition->CreationType(), operand), cilInstruction(definition->SignatureString())
    {
        slotCount = std::max(definition->CreationType()->SlotCount(), operand->CreationType()->SlotCount());
    }

    Enums::MemberType BuiltInCastExpression::MemberType() const { return Enums::MemberType::BuiltInCast; }

    bool BuiltInCastExpression::Readable() const { return true; }
    bool BuiltInCastExpression::Writable() const { return false; }

    std::string BuiltInCastExpression::InstructionGet() const { return cilInstruction; }
    std::string BuiltInCastExpression::InstructionSet() const { return ""; }
}
