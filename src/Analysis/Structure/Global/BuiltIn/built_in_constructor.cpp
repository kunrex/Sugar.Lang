#include "built_in_constructor.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    BuiltInConstructor::BuiltInConstructor(const IDataType* const creationType, const string& instruction) : ConstructorDefinition(Describer::Public, creationType), BuiltInFunction()
    {
        fullName = instruction;
    }

    MemberType BuiltInConstructor::MemberType() const { return MemberType::BuiltInConstructor; }

    const string& BuiltInConstructor::FullName() const { return fullName; }
}

