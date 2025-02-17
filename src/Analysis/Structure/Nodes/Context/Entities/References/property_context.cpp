#include "property_context.h"

#include <format>

#include "../../../../Core/DataTypes/data_type.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    PropertyContext::PropertyContext(const PropertyDefinition* property) : ContextNode(property->CreationType()), property(property)
    {
        slotCount = creationType->SlotCount();
    }

    MemberType PropertyContext::MemberType() const { return MemberType::PropertyContext; }

    bool PropertyContext::Readable() const { return property->Readable(); }
    bool PropertyContext::Writable() const { return property->Readable(); }

    std::string PropertyContext::InstructionGet() const { return property->SignatureGetString(); }
    std::string PropertyContext::InstructionSet() const { return property->SignatureSetString(); }
}
