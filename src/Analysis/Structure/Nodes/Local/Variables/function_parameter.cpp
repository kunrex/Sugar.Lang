#include "function_parameter.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Local
{
    FunctionParameter::FunctionParameter(const std::string& name, const Enums::Describer describer, const Core::DataType* creationType) : LocalVariable(name, describer, creationType)
    {
        fullName = name;
    }

    MemberType FunctionParameter::MemberType() const { return MemberType::FunctionParameter; }
}