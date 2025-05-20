#include "built_in_method.h"

#include "../../Core/DataTypes/data_type.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInMethod::BuiltInMethod(const string& name, const Enums::Describer describer, const Interfaces::IDataType* const creationType, const string& instruction) : MethodDefinition(name, describer, creationType), BuiltInFunction()
    {
        fullName = instruction;
    }

    MemberType BuiltInMethod::MemberType() const { return MemberType::BuiltInDefinition; }

    const string& BuiltInMethod::FullName() const { return fullName; }

    void BuiltInMethod::Bind()
    { }
}
