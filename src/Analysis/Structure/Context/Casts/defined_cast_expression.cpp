#include "defined_cast_expression.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    DefinedCastExpression::DefinedCastExpression(const IFunction* const definition, const ContextNode* const operand) : UnaryContextNode(definition->CreationType(), operand), definition(definition)
    {
        slotCount = std::max(definition->CreationType()->SlotCount(), operand->CreationType()->SlotCount());
    }

    MemberType DefinedCastExpression::MemberType() const { return MemberType::DefinedCast; }

    int DefinedCastExpression::SlotCount() const { return slotCount; }

    bool DefinedCastExpression::Readable() const { return true; }
    bool DefinedCastExpression::Writable() const { return false; }

    string DefinedCastExpression::CILInstruction() const { return std::format("call {}", definition->FullName()); }
}
