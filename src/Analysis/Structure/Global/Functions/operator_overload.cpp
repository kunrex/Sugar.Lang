#include "operator_overload.h"

#include <format>

#include "function_extensions.h"
#include "../../../../Exceptions/Compilation/Analysis/Local/return_value_exception.h"
#include "../../../Creation/Binding/binder_extensions.h"

#include "../../Core/DataTypes/data_type.h"

#include "../../../Creation/Binding/local_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

using namespace std;

using namespace Services;

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Transpiling;

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

    void OperatorOverload::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);

        if (!IsReturnComplete(scope, creationType))
            PushException(new Exceptions::ReturnValueException(parseNode->Token().Index(), parent->Parent()));
    }

    void OperatorOverload::Transpile(StringBuilder& builder) const
    {
        builder.PushLine("");
        builder.PushLine(std::format(".method {} final {} {} {}({}) cil managed", AccessModifierString(this), StaticModifierString(this), creationType->FullName(), name, ScopedParameterString(this)));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 0;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        TranspileScope(scope, innerBuilder, maxSlotSize);

        builder.PushLine(std::format(".maxstack {}", maxSlotSize));
        if (children.size() - parameterCount > 0)
            builder.PushLine(std::format(".localsinit({})", ScopedLocalVariableString(this)));

        builder.Push(innerBuilder.Value());

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }
}
