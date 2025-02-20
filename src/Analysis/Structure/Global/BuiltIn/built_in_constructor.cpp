#include "built_in_constructor.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInConstructor::BuiltInConstructor(const DataType* const creationType, const string& instruction) : ConstructorDefinition(Describer::Public, creationType), parameters()
    {
        fullName = instruction;
    }

    MemberType BuiltInConstructor::MemberType() const { return MemberType::BuiltInConstructor; }

    const string& BuiltInConstructor::FullName() const { return fullName; }

    unsigned long BuiltInConstructor::ParameterCount() const { return parameters.size(); }

    const DataType* BuiltInConstructor::ParameterAt(const unsigned long index) const { return parameters.at(index); }

    void BuiltInConstructor::PushParameterType(const DataType* type)
    {
        parameters.push_back(type);
    }
}

