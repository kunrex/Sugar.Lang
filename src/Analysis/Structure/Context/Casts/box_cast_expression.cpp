#include "box_cast_expression.h"

#include <format>

#include "../../Wrappers/Reference/object.h"

using namespace std;

using namespace ParseNodes::Enums;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Context
{
    BoxCastExpression::BoxCastExpression(const IContextNode* const operand) : UnaryContextNode(&Object::Instance(), operand), slotCount(std::max(Object::Instance().SlotCount(), operand->SlotCount()))
    { }

    MemberType BoxCastExpression::MemberType() const { return MemberType::CastExpression; }

    int BoxCastExpression::SlotCount() const { return slotCount; }

    bool BoxCastExpression::Readable() const { return true; }
    bool BoxCastExpression::Writable() const { return false; }

    string BoxCastExpression::CILData() const { return std::format("box {}", GetChild(static_cast<int>(ChildCode::Expression))->CreationType()->FullName()); }
}
