#include "implicit_cast.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    ImplicitCast::ImplicitCast(const Enums::Describer describer, const DataType* creationType, const ScopeNode* body) : CastDefinition(describer, creationType), Scoped(body)
    { }

    MemberType ImplicitCast::MemberType() const { return MemberType::ImplicitCast; }

    const std::string& ImplicitCast::FullName() const
    {
        if (fullName.empty())
            fullName = parent->FullName() + "::__implicit__" + creationType->FullName();

        return fullName;
    }

    const std::string& ImplicitCast::SignatureString() const
    {
        if (signature.empty())
            signature = std::format("{} {}{}", creationType->FullName(), FullName(), ArgumentSignatureString());

        return signature;
    }

    void ImplicitCast::AddArgument(const Creation::Variable* parameter)
    {
        Scoped::AddArgument(parameter);
        PushParameterType(parameter->CreationType());
    }
}
