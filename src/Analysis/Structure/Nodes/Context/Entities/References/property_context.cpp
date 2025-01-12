#include "property_context.h"

#include <format>

#include "../../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    PropertyContext::PropertyContext(const Property* property) : ContextNode(property->CreationType()), property(property)
    { }

    MemberType PropertyContext::MemberType() const { return MemberType::PropertyContext; }

    std::string PropertyContext::InstructionGet() const { return std::format("call instance {} {}::{}()", property->CreationType()->FullName(), property->Parent()->FullName(), get_property); }
    std::string PropertyContext::InstructionSet() const { return std::format("call instance void {}::{}({})", property->Parent()->FullName(), set_property, property->CreationType()->FullName()); }
}
