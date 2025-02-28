#include "field_address_context.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    FieldAddressContext::FieldAddressContext(const IVariable* const variable) : VariableContext(variable, true)
    { }

    MemberType FieldAddressContext::MemberType() const { return MemberType::FieldContext; }

    int FieldAddressContext::SlotCount() const { return 1; }

    bool FieldAddressContext::Writable() const { return false; }

    string FieldAddressContext::CILInstruction() const
    {
        if (variable->CheckDescriber(Describer::Static))
            return std::format("ldsflda {} {}", creationType->FullName(), variable->FullName());

        return std::format("ldflda {} {}", creationType->FullName(), variable->FullName());
    }
}
