#include "enum_field.h"

#include "../../Wrappers/Value/integer.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    EnumField::EnumField(const string& name, const Enums::Describer describer) : GlobalVariable(name, describer, &Integer::Instance()), compiled(false), dependencies()
    { }

    EnumField::EnumField(const string& name, const Enums::Describer describer, const ParseNodes::ParseNode* parseNode) : GlobalVariable(name, describer, &Integer::Instance(), parseNode), compiled(false), dependencies()
    { }

    MemberType EnumField::MemberType() const { return MemberType::EnumField; }

    const std::string& EnumField::FullName() const { return fullName; }

    bool EnumField::Readable() const { return compiled; }
    bool EnumField::Writable() const { return false; }

    void EnumField::Compile(const std::string& value)
    {
        if (!compiled)
        {
            fullName = value;
            compiled = true;
        }
    }

    void EnumField::PushDependency(const ICharacteristic* constant)
    {
        dependencies.push_back(constant);
    }

    bool EnumField::IsDependent(const ICharacteristic* constant) const
    {
        for (const auto dependency : dependencies)
            if (constant == dependency)
                return true;

        return false;
    }
}