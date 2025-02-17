#include "box_cast_expression.h"

#include <format>

#include "../../../Wrappers/Reference/object.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Structure
{
    BoxCastExpression::BoxCastExpression(const ContextNode* operand) : UnaryContextNode(&Object::Instance(), operand), cilInstruction(std::format("box {}", operand->CreationType()->FullName()))
    {
        slotCount = std::max(Object::Instance().SlotCount(), operand->SlotCount());
    }

    MemberType BoxCastExpression::MemberType() const { return MemberType::BoxCast; }

    bool BoxCastExpression::Readable() const { return true; }
    bool BoxCastExpression::Writable() const { return false; }

    std::string BoxCastExpression::InstructionGet() const { return cilInstruction; }
    std::string BoxCastExpression::InstructionSet() const { return ""; }
}
