#include "built_in_void.h"

#include "../../Core/DataTypes/data_type.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInVoid::BuiltInVoid(const std::string& name, const Enums::Describer describer, const string& instruction) : VoidDefinition(name, describer), parameters()
    {
        fullName = instruction;
    }

    MemberType BuiltInVoid::MemberType() const { return MemberType::BuiltInDefinition; }

    const string& BuiltInVoid::FullName() const { return fullName; }

    unsigned long BuiltInVoid::ParameterCount() const { return parameters.size(); }

    const DataType* BuiltInVoid::ParameterAt(const unsigned long index) const { return parameters.at(index); }
}
