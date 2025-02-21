#include "operator_overload.h"

#include <format>

#include "function_extensions.h"

#include "../../Core/DataTypes/data_type.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    OperatorOverload::OperatorOverload(const SyntaxKind baseOperator, const Enums::Describer describer, const DataType* const creationType, const Groups::ScopeNode* const body) : Nameable(std::format("__operator__{}", static_cast<short>(baseOperator))), OverloadDefinition(baseOperator, describer, creationType), Scoped(body)
    { }

    MemberType OperatorOverload::MemberType() const { return MemberType::OperatorOverload; }

    const string& OperatorOverload::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("call {} {} {}::{}{}", creationType->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    unsigned long OperatorOverload::ParameterCount() const { return parameterCount; }

    const DataType* OperatorOverload::ParameterAt(const unsigned long index) const { return VariableAt(index)->CreationType(); }
}
