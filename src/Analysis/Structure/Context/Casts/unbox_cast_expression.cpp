#include "unbox_cast_expression.h"

#include <format>

#include "../../Wrappers/Reference/object.h"
#include "../../DataTypes/class.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    UnboxCastExpression::UnboxCastExpression(const IDataType* const creationType, const ContextNode* const operand) : UnaryContextNode(creationType, operand)
    {
        slotCount = std::max(Object::Instance().SlotCount(), creationType->SlotCount());
    }

    int UnboxCastExpression::SlotCount() const { return slotCount; }

    MemberType UnboxCastExpression::MemberType() const { return MemberType::UnboxCast; }

    bool UnboxCastExpression::Readable() const { return true; }
    bool UnboxCastExpression::Writable() const { return false; }

    string UnboxCastExpression::CILInstruction() const { return std::format("box {}", creationType->FullName()); }
}

