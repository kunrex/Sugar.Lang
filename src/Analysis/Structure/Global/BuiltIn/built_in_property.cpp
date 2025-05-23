#include "built_in_property.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInProperty::BuiltInProperty(const string& name, const Enums::Describer describer, const Interfaces::IDataType* creationType, const bool readable, const string& getInstruction, const bool writable, const string& setInstruction) : PropertyDefinition(name, describer, creationType, nullptr), readable(readable), writable(writable)
    {
        this->getInstruction = getInstruction;
        this->setInstruction = setInstruction;
    }

    MemberType BuiltInProperty::MemberType() const { return MemberType::BuiltInProperty; }

    const std::string& BuiltInProperty::FullName() const { return name; }

    bool BuiltInProperty::Readable() const { return readable; }
    bool BuiltInProperty::Writable() const { return writable; }

    const std::string& BuiltInProperty::SignatureGetString() const { return getInstruction; }
    const std::string& BuiltInProperty::SignatureSetString() const { return setInstruction; }

    void BuiltInProperty::BindLocal()
    { }
}
