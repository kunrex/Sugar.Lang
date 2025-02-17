#include "built_in_cast.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInCast::BuiltInCast(const DataType* creationType, const string& instruction) : CastDefinition(Describer::PublicStatic, creationType())
    {
        signature = instruction;
    }

    MemberType BuiltInCast::MemberType() const { return MemberType::BuiltInCast; }
    const std::string& BuiltInCast::SignatureString() const { return signature; }
}
