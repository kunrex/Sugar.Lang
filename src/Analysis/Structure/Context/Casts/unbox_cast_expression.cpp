#include "unbox_cast_expression.h"

#include <format>

#include "../../../Wrappers/Reference/object.h"
#include "../../DataTypes/class.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Structure
{
    UnboxCastExpression::UnboxCastExpression(const DataType* creationType, const ContextNode* operand) : UnaryContextNode(creationType, operand), cilInstruction(std::format("box {}", creationType->FullName()))
    {
        slotCount = std::max(Object::Instance().SlotCount(), creationType->SlotCount());
    }

    MemberType UnboxCastExpression::MemberType() const { return MemberType::UnboxCast; }

    bool UnboxCastExpression::Readable() const { return true; }
    bool UnboxCastExpression::Writable() const { return false; }

    std::string UnboxCastExpression::InstructionGet() const { return cilInstruction; }
    std::string UnboxCastExpression::InstructionSet() const { return ""; }
}

