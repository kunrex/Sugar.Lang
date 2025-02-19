#include "built_in_method.h"

#include "../../Core/DataTypes/data_type.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInMethod::BuiltInMethod(const Enums::Describer describer, const DataType* const creationType, const string& instruction) : MethodDefinition(instruction, describer, creationType), parameters()
    { }

    MemberType BuiltInMethod::MemberType() const { return MemberType::BuiltInDefinition; }

    const string& BuiltInMethod::FullName() const { return name; }
    const string& BuiltInMethod::SignatureString() const { return name; }
    const string& BuiltInMethod::ArgumentSignatureString() const { return name; }

    unsigned long BuiltInMethod::ParameterCount() const { return parameters.size(); }

    const DataType* BuiltInMethod::ParameterAt(const unsigned long index) const { return parameters.at(index); }
}
