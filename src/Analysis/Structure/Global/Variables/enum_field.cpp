#include "enum_field.h"

#include "../../Wrappers/Value/integer.h"

using namespace std;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    EnumField::EnumField(const string& name, const Enums::Describer describer) : GlobalVariable(name, describer, &Integer::Instance()), dependencies()
    { }

    EnumField::EnumField(const string& name, const Enums::Describer describer, const IParseNode* const parseNode) : GlobalVariable(name, describer, &Integer::Instance(), parseNode), dependencies()
    { }

    MemberType EnumField::MemberType() const { return MemberType::EnumField; }

    const std::string& EnumField::FullName() const { return fullName; }

    bool EnumField::Readable() const { return true; }
    bool EnumField::Writable() const { return false; }

    bool EnumField::Compiled() const { return context != nullptr; }

    void EnumField::PushDependency(const IConstant* constant) const
    {
        dependencies.push_back(constant);
    }

    bool EnumField::IsDependent(const IConstant* constant) const
    {
        for (const auto dependency : dependencies)
            if (constant == dependency || dependency->IsDependent(constant))
                return true;

        return false;
    }
}