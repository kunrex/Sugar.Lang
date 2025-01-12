#include "unbox_instruction.h"

#include <format>

#include "../../DataTypes/class.h"

using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Structure
{
    UnBoxInstruction::UnBoxInstruction(const DataType* creationType, const ContextNode* operand) : UnaryContextNode(creationType, operand)
    { }

    [[nodiscard]] int UnBoxInstruction::SlotCount() const { return creationType->SlotCount(); }

    std::string UnBoxInstruction::InstructionGet() const { return std::format("box {}", creationType->FullName());}
    std::string UnBoxInstruction::InstructionSet() const { return ""; }
}

