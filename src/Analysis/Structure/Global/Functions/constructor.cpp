#include "constructor.h"

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
    Constructor::Constructor(const Enums::Describer describer, const DataType* const creationType, const ScopeNode* const body) : Nameable(".ctor"), ConstructorDefinition(describer, creationType), Scoped(body)
    { }

    MemberType Constructor::MemberType() const { return MemberType::Constructor; }

    const string& Constructor::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("instance void {} {}::{}{}", parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    unsigned long Constructor::ParameterCount() const { return argumentCount; }

    const DataType* Constructor::ParameterAt(const unsigned long index) const { return VariableAt(index)->CreationType(); }
}

