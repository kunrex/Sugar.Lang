#include "function_parameter.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Local
{
    FunctionParameter::FunctionParameter(const std::string& name, const Enums::Describer describer, const DataType* const creationType) : LocalVariable(name, describer, creationType)
    { }

    MemberType FunctionParameter::MemberType() const { return MemberType::FunctionParameter; }
}