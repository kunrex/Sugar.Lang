#include "parameter_context.h"

#include "../../../Core/Interfaces/DataTypes/i_data_type.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    ParameterContext::ParameterContext(const IVariable* const variable, const int index) : LocalVariableContext(variable, index)
    { }

    MemberType ParameterContext::MemberType() const { return MemberType::FunctionParameterContext; }

    std::string ParameterContext::CILData() const { return std::to_string(index); }

    void ParameterContext::Print(const std::string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Parameter Context: " << variable->FullName() << "; Index: " << index << std::endl;
    }
}
