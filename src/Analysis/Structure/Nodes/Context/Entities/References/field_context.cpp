#include "field_context.h"

#include "../../../../Core/DataTypes/data_type.h"

#include <format>

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    FieldContext::FieldContext(const Variable* variable) : VariableContext(variable)
    { }

    MemberType FieldContext::MemberType() const { return MemberType::FieldContext; }

    std::string FieldContext::InstructionGet() const { return std::format("ldfld {} {}", creationType->FullName(), variable->FullName()); }
    std::string FieldContext::InstructionSet() const { return std::format("stfld {} {}", creationType->FullName(), variable->FullName()); }
}
