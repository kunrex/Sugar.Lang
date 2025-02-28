#include "field_context.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    FieldContext::FieldContext(const IVariable* const variable, const bool isLoadInstruction) : VariableContext(variable, isLoadInstruction)
    { }

    MemberType FieldContext::MemberType() const { return MemberType::FieldContext; }

    int FieldContext::SlotCount() const { return creationType->SlotCount(); }

    string FieldContext::CILInstruction() const
    {
        if (isLoadInstruction)
        {
            if (variable->CheckDescriber(Describer::Static))
                return std::format("ldsfld {} {}", creationType->FullName(), variable->FullName());

            return std::format("ldfld {} {}", creationType->FullName(), variable->FullName());
        }

        if (variable->CheckDescriber(Describer::Static))
            return std::format("stsfld {} {}", creationType->FullName(), variable->FullName());

        return std::format("stfld {} {}", creationType->FullName(), variable->FullName());
    }
}
