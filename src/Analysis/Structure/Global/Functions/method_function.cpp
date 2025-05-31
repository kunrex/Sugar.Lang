#include "method_function.h"

#include <format>

#include "function_extensions.h"
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
    MethodFunction::MethodFunction(const string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : MethodDefinition(name, describer, creationType), Scoped(body)
    { }

    MemberType MethodFunction::MemberType() const { return MemberType::MethodDefinition; }

    const string& MethodFunction::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} {} {} {}::{}{}",  CheckDescriber(Describer::Static) ? "" : "instance", creationType->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    void MethodFunction::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);

        if (!IsReturnComplete(scope, creationType))
            PushException(new ReturnValueException(parseNode->Token().Index(), parent->Parent()));
    }

    void MethodFunction::Transpile(StringBuilder& builder) const
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

    GeneratedGetFunction::GeneratedGetFunction(const Enums::Describer describer, std::string name, const IDataType* const creationType) : MethodDefinition("__get__" + name, describer, creationType), DefaultScoped(), name(std::move(name))
    { }

    MemberType GeneratedGetFunction::MemberType() const { return MemberType::VoidDefinition; }

    const std::string& GeneratedGetFunction::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} {} {} {}::{}()",  CheckDescriber(Describer::Static) ? "" : "instance", creationType->FullName(), parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name);

        return fullName;
    }

    void GeneratedGetFunction::BindLocal()
    { }

    void GeneratedGetFunction::Transpile(StringBuilder& builder) const
    {
        builder.PushLine("");
        builder.PushLine(std::format(".method {} final {} void () cil managed", AccessModifierString(this), StaticModifierString(this), name));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        builder.PushLine(".maxstack 1");
        builder.PushLine(load_this);
        builder.PushLine(std::format("ld{}fld {} {}", CheckDescriber(Describer::Static) ? "s" : "", creationType->FullName(), parent->FindCharacteristic(name)->FullName()));
        builder.PushLine("ret");

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }
}
