#include "explicit_cast.h"

#include <format>

#include "function_extensions.h"
#include "../../../../Exceptions/Compilation/Analysis/Local/accessibility_exception.h"
#include "../../../../Exceptions/Compilation/Analysis/Local/return_value_exception.h"
#include "../../../Creation/Binding/binder_extensions.h"

#include "../../Core/DataTypes/data_type.h"

#include "../../../Creation/Binding/local_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

using namespace std;

using namespace Services;

using namespace Exceptions;

using namespace ParseNodes;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Creation::Binding;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    ExplicitCast::ExplicitCast(const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : Nameable(std::format("__explicit__{}", creationType->Name())), CastDefinition(describer, creationType), Scoped(body)
    { }

    MemberType ExplicitCast::MemberType() const { return MemberType::ExplicitCast; }

    const string& ExplicitCast::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("call {} {} {}::{}{}", creationType->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    void ExplicitCast::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);

        if (!IsReturnComplete(scope, creationType))
            PushException(new ReturnValueException(parseNode->Token().Index(), parent->Parent()));
    }

    void ExplicitCast::Transpile(StringBuilder& builder) const
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
        builder.PushLine(std::format(".localsinit({})", ScopedLocalVariableString(this)));

        builder.Push(innerBuilder.Value());

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }
}
