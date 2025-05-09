#include "property.h"

#include <format>

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    Property::Property(const string& name, const Enums::Describer describer, const IDataType* const creationType, const MethodDefinition* const get, const VoidDefinition* const set) : PropertyDefinition(name, describer, creationType, nullptr), readable(false), getInstruction(), writable(false), setInstruction()
    {
        if (get != nullptr)
        {
            readable = true;
            getInstruction = std::format("call {}", get->FullName());
        }

        if (set != nullptr)
        {
            writable = true;
            setInstruction = std::format("call {}", set->FullName());
        }
    }

    Property::Property(const string& name, const Enums::Describer describer, const IDataType* const creationType, const MethodDefinition* const get, const VoidDefinition* const set, const IParseNode* const value) : PropertyDefinition(name, describer, creationType, value), readable(false), getInstruction(), writable(false), setInstruction()
    {
        if (get != nullptr)
        {
            readable = true;
            getInstruction = std::format("call {}", get->FullName());
        }

        if (set != nullptr)
        {
            writable = true;
            setInstruction = std::format("call {}", set->FullName());
        }
    }

    MemberType Property::MemberType() const { return MemberType::Property; }

    const std::string& Property::FullName() const
    {
        if (fullName.empty())
            fullName = parent->FullName() + "::" + name;

        return fullName;
    }

    bool Property::Readable() const { return readable; }
    bool Property::Writable() const { return writable; }

    const std::string& Property::SignatureGetString() const { return getInstruction; }
    const std::string& Property::SignatureSetString() const { return setInstruction; }
}
