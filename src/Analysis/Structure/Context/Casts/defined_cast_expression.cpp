#include "defined_cast_expression.h"

#include <format>

#include "../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    DefinedCastExpression::DefinedCastExpression(const IFunction* const definition, const IContextNode* const operand) : UnaryContextNode(definition->CreationType(), operand), slotCount(std::max(definition->CreationType()->SlotCount(), operand->CreationType()->SlotCount())), definition(definition)
    { }

    MemberType DefinedCastExpression::MemberType() const { return MemberType::CastExpression; }

    int DefinedCastExpression::SlotCount() const { return slotCount; }

    bool DefinedCastExpression::Readable() const { return true; }
    bool DefinedCastExpression::Writable() const { return false; }

    string DefinedCastExpression::CILData() const { return definition->MemberType() == MemberType::BuiltInCast ? definition->FullName() : std::format("call {}", definition->FullName()); }
}
