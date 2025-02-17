#include "void_definition.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    VoidDefinition::VoidDefinition(const string& name, const Enums::Describer describer) : FunctionDefinition(name, describer, nullptr)
    { }

    MemberType VoidDefinition::MemberType() const { return MemberType::VoidDefinition; }
    bool VoidDefinition::Readable() const { return false; }

    const std::string& VoidDefinition::FullName() const
    {
        if (fullName.empty())
            fullName = std::format("{}::{}", parent->FullName(), name);

        return  fullName;
    }

    const std::string& VoidDefinition::SignatureString() const
    {
        if (signature.empty())
            signature = std::format("void {}{}", FullName(), ArgumentSignatureString());

        return signature;
    }
}
