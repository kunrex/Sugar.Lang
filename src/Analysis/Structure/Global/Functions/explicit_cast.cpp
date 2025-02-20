#include "explicit_cast.h"

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
    ExplicitCast::ExplicitCast(const Enums::Describer describer, const DataType* const creationType, const ScopeNode* const body) : Nameable(std::format("__explicit__{}", creationType->Name())), CastDefinition(describer, creationType), Scoped(body)
    { }

    MemberType ExplicitCast::MemberType() const { return MemberType::ExplicitCast; }

    const string& ExplicitCast::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} {} {}::{}{}", creationType->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    unsigned long ExplicitCast::ParameterCount() const { return argumentCount; }

    const DataType* ExplicitCast::ParameterAt(const unsigned long index) const { return VariableAt(index)->CreationType(); }
}
