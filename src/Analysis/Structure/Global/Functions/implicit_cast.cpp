#include "implicit_cast.h"

#include <format>

#include "function_extensions.h"

#include "../../Core/DataTypes/data_type.h"

#include "../../../Creation/Binding/local_binder.h"

using namespace std;

using namespace ParseNodes;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Creation::Binding;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    ImplicitCast::ImplicitCast(const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : Nameable(std::format("__implicit__{}", creationType->Name())), CastDefinition(describer, creationType), Scoped(body)
    { }

    MemberType ImplicitCast::MemberType() const { return MemberType::ImplicitCast; }

    const string& ImplicitCast::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("call {} {} {}::{}{}", creationType->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    void ImplicitCast::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);
    }
}
