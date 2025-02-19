#include "built_in_cast.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInCast::BuiltInCast(const DataType* const creationType, const string& instruction) : CastDefinition(Describer::PublicStatic, creationType()), parameters()
    {
        signature = instruction;
    }

    MemberType BuiltInCast::MemberType() const { return MemberType::BuiltInCast; }

    const string& BuiltInCast::SignatureString() const { return signature; }

    const string& BuiltInCast::ArgumentSignatureString() const { return signature;}

    unsigned long BuiltInCast::ParameterCount() const { return parameters.size(); }

    const DataType* BuiltInCast::ParameterAt(const unsigned long index) const { return parameters.at(index); }
}
