#include "built_in_void.h"

#include "../../Core/DataTypes/data_type.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInVoid::BuiltInVoid(const Enums::Describer describer, const string& instruction) : VoidDefinition(instruction, describer), parameters()
    { }

    MemberType BuiltInVoid::MemberType() const { return MemberType::BuiltInDefinition; }

    const string& BuiltInVoid::FullName() const { return name; }
    const string& BuiltInVoid::SignatureString() const { return name; }
    const string& BuiltInVoid::ArgumentSignatureString() const { return name; }

    unsigned long BuiltInVoid::ParameterCount() const { return parameters.size(); }

    const DataType* BuiltInVoid::ParameterAt(const unsigned long index) const { return parameters.at(index); }
}
