#include "explicit_cast.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    ExplicitCast::ExplicitCast(const Enums::Describer describer, const DataType* creationType, const ScopeNode* body) : CastDefinition(describer, creationType), Scoped(body)
    { }

    MemberType ExplicitCast::MemberType() const { return MemberType::ExplicitCast; }

    const std::string& ExplicitCast::FullName() const
    {
        if (fullName.empty())
            fullName = parent->FullName() + "::__explicit__" + creationType->FullName();

        return fullName;
    }

    const std::string& ExplicitCast::SignatureString() const
    {
        if (signature.empty())
            signature = std::format("{} {}{}", creationType->FullName(), FullName(), ArgumentSignatureString());

        return signature;
    }

    void ExplicitCast::AddArgument(const Creation::Variable* parameter)
    {
        Scoped::AddArgument(parameter);
        PushParameterType(parameter->CreationType());
    }
}
