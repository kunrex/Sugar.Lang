#include "field_context.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    FieldContext::FieldContext(const IVariable* const variable, const bool bypassWrite) : VariableContext(variable), writable(variable->Writable() && (variable->CheckDescriber(Describer::Const) && bypassWrite))
    { }

    MemberType FieldContext::MemberType() const { return MemberType::FieldContext; }

    int FieldContext::SlotCount() const { return creationType->SlotCount(); }

    bool FieldContext::Writable() const { return writable; }
}
