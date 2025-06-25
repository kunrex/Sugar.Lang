#include "defined_cast_expression.h"

#include <format>

#include "../../Core/Interfaces/DataTypes/i_data_type.h"

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

    std::string DefinedCastExpression::CILData() const { return definition->FullName(); }

    void DefinedCastExpression::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Defined Cast Expression: " << definition->CreationType()->FullName() << std::endl;
        FixedContextCollection::Print(indent, last);
    }
}
