#include "built_in_cast_expression.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    BuiltInCastExpression::BuiltInCastExpression(const IFunction* const definition, const ContextNode* const operand) : UnaryContextNode(definition->CreationType(), operand), definition(definition)
    {
        slotCount = std::max(definition->CreationType()->SlotCount(), operand->CreationType()->SlotCount());
    }

    Enums::MemberType BuiltInCastExpression::MemberType() const { return Enums::MemberType::BuiltInCast; }

    int BuiltInCastExpression::SlotCount() const { return slotCount;}

    bool BuiltInCastExpression::Readable() const { return true; }
    bool BuiltInCastExpression::Writable() const { return false; }

    string BuiltInCastExpression::CILData() const { return definition->FullName(); }
}
