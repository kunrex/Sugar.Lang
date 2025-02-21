#include "implicit_cast.h"

#include <format>

#include "function_extensions.h"

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    ImplicitCast::ImplicitCast(const Enums::Describer describer, const DataType* const creationType, const ScopeNode* const body) : Nameable(std::format("__implicit__{}", creationType->Name())), CastDefinition(describer, creationType), Scoped(body)
    { }

    MemberType ImplicitCast::MemberType() const { return MemberType::ImplicitCast; }

    const string& ImplicitCast::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("call {} {} {}::{}{}", creationType->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    unsigned long ImplicitCast::ParameterCount() const { return parameterCount; }

    const DataType* ImplicitCast::ParameterAt(const unsigned long index) const { return VariableAt(index)->CreationType(); }
}
