#include "constructor.h"

#include <format>

#include "../../../Core/DataTypes/data_type.h"

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    Constructor::Constructor(const Enums::Describer describer, const DataType* creationType, const ScopeNode* body) : ConstructorDefinition(describer, creationType), Scoped(body)
    { }

    MemberType Constructor::MemberType() const { return MemberType::Constructor; }

    const std::string& Constructor::FullName() const
    {
        if (fullName.empty())
            fullName = parent->FullName() + "::.ctor";

        return fullName;
    }

    const std::string& Constructor::SignatureString() const
    {
        if (signature.empty())
            signature = std::format("void {}{}", FullName(), ArgumentSignatureString());

        return signature;
    }

    void Constructor::AddArgument(const Creation::Variable* parameter)
    {
        Scoped::AddArgument(parameter);
        PushParameterType(parameter->CreationType());
    }
}

