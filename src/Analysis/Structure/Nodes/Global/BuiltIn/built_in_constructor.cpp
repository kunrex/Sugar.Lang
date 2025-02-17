#include "built_in_constructor.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInConstructor::BuiltInConstructor(const DataType* creationType, const string& instruction) : ConstructorDefinition(Describer::Public, creationType)
    {
        signature = instruction;
    }

    MemberType BuiltInConstructor::MemberType() const { return MemberType::BuiltInConstructor; }

    const std::string& BuiltInConstructor::SignatureString() const { return signature; }
}

