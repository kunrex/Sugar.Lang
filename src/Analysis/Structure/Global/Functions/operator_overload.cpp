#include "operator_overload.h"

#include <format>

#include "function_extensions.h"

#include "../../Core/DataTypes/data_type.h"

#include "../../../Creation/Binding/local_binder.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Creation::Binding;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    OperatorOverload::OperatorOverload(const SyntaxKind baseOperator, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : Nameable(std::format("__operator__{}", static_cast<short>(baseOperator))), OverloadDefinition(baseOperator, describer, creationType), Scoped(body)
    { }

    MemberType OperatorOverload::MemberType() const { return MemberType::OperatorOverload; }

    const string& OperatorOverload::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("call {} {} {}::{}{}", creationType->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    void OperatorOverload::Bind()
    {
        BindScoped(this);
    }
}
