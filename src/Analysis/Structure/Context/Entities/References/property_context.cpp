#include "property_context.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    PropertyContext::PropertyContext(const PropertyDefinition* const property) : ContextNode(property->CreationType()), property(property)
    { }

    MemberType PropertyContext::MemberType() const { return MemberType::PropertyContext; }

    int PropertyContext::SlotCount() const { return creationType->SlotCount(); }

    bool PropertyContext::Readable() const { return property->Readable() && creationType->MemberType() == MemberType::Class; }
    bool PropertyContext::Writable() const { return property->Writable(); }

    uintptr_t PropertyContext::Metadata() const { return reinterpret_cast<uintptr_t>(property); }
    string PropertyContext::CILData() const { return ""; }
}
