#include "property_context.h"

#include <format>

#include "../../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

namespace Analysis::Structure::Context
{
    PropertyContext::PropertyContext(const PropertyDefinition* const property, const bool isPublic) : ContextNode(property->CreationType()), isPublic(isPublic), property(property)
    { }

    MemberType PropertyContext::MemberType() const { return MemberType::PropertyContext; }

    int PropertyContext::SlotCount() const { return creationType->SlotCount(); }

    bool PropertyContext::Readable() const { return property->Readable() && creationType->MemberType() == MemberType::Class && !isPublic || property->PublicGet(); }
    bool PropertyContext::Writable() const { return property->Writable() && !isPublic || property->PublicSet(); }

    uintptr_t PropertyContext::Metadata() const { return reinterpret_cast<uintptr_t>(property); }
    std::string PropertyContext::CILData() const { return ""; }

    void PropertyContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Property Context: " << property->FullName() << std::endl;
    }
}
