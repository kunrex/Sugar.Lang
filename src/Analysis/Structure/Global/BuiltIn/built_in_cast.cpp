#include "built_in_cast.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    BuiltInCast::BuiltInCast(const IDataType* const creationType, const string& instruction) : CastDefinition(Describer::PublicStatic, creationType), BuiltInFunction()
    {
        fullName = instruction;
    }

    MemberType BuiltInCast::MemberType() const { return MemberType::BuiltInCast; }

    const string& BuiltInCast::FullName() const { return fullName; }
}
