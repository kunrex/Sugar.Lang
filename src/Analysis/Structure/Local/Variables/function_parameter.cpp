#include "function_parameter.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Local
{
    FunctionParameter::FunctionParameter(const std::string& name, const Enums::Describer describer, const IDataType* const creationType) : LocalVariable(name, describer, creationType)
    { }

    MemberType FunctionParameter::MemberType() const { return MemberType::FunctionParameter; }
}