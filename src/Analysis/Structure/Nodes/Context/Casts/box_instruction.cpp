#include "box_instruction.h"

#include <format>

#include "../../DataTypes/class.h"

using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Structure
{
    BoxInstruction::BoxInstruction(const ContextNode* operand) : UnaryContextNode(DataTypes::Class.Object, operand)
    { }

    [[nodiscard]] int BoxInstruction::SlotCount() const { return operand->CreationType()->SlotCount(); }

    std::string BoxInstruction::InstructionGet() const { return std::format("box {}", operand->CreationType()->FullName());}
    std::string BoxInstruction::InstructionSet() const { return ""; }
}
