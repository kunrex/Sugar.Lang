#include "built_in_void.h"

#include "../../Core/DataTypes/data_type.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInVoid::BuiltInVoid(const std::string& name, const Enums::Describer describer, const string& instruction) : VoidDefinition(name, describer), BuiltInFunction()
    {
        fullName = instruction;
    }

    MemberType BuiltInVoid::MemberType() const { return MemberType::BuiltInDefinition; }

    const string& BuiltInVoid::FullName() const { return fullName; }
}
