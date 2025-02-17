#include "method_definition.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    MethodDefinition::MethodDefinition(const string& name, const Enums::Describer describer, const DataType* creationType) : FunctionDefinition(name, describer, creationType)
    { }

    MemberType MethodDefinition::MemberType() const { return MemberType::MethodDefinition; }

    const std::string& MethodDefinition::FullName() const
    {
        if (fullName.empty())
            fullName = std::format("{}::{}", parent->FullName(), name);

        return fullName;
    }

    const std::string& MethodDefinition::SignatureString() const
    {
        if (signature.empty())
            signature = std::format("{} {}{}", creationType->FullName(), FullName(), ArgumentSignatureString());

        return signature;
    }
}
