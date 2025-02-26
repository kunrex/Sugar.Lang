#include "explicit_cast.h"

#include <format>

#include "function_extensions.h"

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    ExplicitCast::ExplicitCast(const Enums::Describer describer, const IDataType* const creationType, const NodeCollection<ParseNodes::ParseNode>* const body) : Nameable(std::format("__explicit__{}", creationType->Name())), CastDefinition(describer, creationType), Scoped(body)
    { }

    MemberType ExplicitCast::MemberType() const { return MemberType::ExplicitCast; }

    const string& ExplicitCast::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("call {} {} {}::{}{}", creationType->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }
}
