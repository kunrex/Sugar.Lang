#include "built_in_constructor.h"

#include "built_in_operation.h"

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

    void BuiltInConstructor::BindLocal()
    { }

    void BuiltInConstructor::Transpile(Services::StringBuilder& builder) const
    { }

    void BuiltInConstructor::PushTranspilation(Services::StringBuilder& builder) const
    { }

    void BuiltInConstructor::PushTranspilation(const ICharacteristic* const characteristic)
    { }
}

