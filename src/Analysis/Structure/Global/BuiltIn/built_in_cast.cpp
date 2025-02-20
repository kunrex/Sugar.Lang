#include "built_in_cast.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInCast::BuiltInCast(const DataType* const creationType, const string& instruction) : CastDefinition(Describer::PublicStatic, creationType()), parameters()
    {
        fullName = instruction;
    }

    MemberType BuiltInCast::MemberType() const { return MemberType::BuiltInCast; }

    const string& BuiltInCast::FullName() const { return fullName; }

    unsigned long BuiltInCast::ParameterCount() const { return parameters.size(); }

    const DataType* BuiltInCast::ParameterAt(const unsigned long index) const { return parameters.at(index); }

    void BuiltInCast::PushParameterType(const DataType* type)
    {
        parameters.push_back(type);
    }
}
