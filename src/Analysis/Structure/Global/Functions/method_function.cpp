#include "method_function.h"

#include <format>

#include "../../../../Exceptions/exception_manager.h"
#include "../../Core/DataTypes/data_type.h"

#include "../../../Creation/Binding/local_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

#include "../../../../Exceptions/Compilation/Analysis/Local/return_value_exception.h"

using namespace Services;

using namespace Exceptions;

using namespace ParseNodes;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    MethodFunction::MethodFunction(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : MethodDefinition(name, describer, creationType), Scoped(body)
    { }

    MemberType MethodFunction::MemberType() const { return MemberType::MethodDefinition; }

    const std::string& MethodFunction::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} {} {} {}::{}{}",  CheckDescriber(Describer::Static) ? "call" : "callvirt instance", creationType->MemberType() == MemberType::Class ? "class" : "valuetype", creationType->FullName(), parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    void MethodFunction::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);

        if (!IsReturnComplete(scope, creationType))
            ExceptionManager::PushException(ReturnValueException(parseNode->Token().Index(), parent->Parent()));
    }

    void MethodFunction::Transpile(StringBuilder& builder) const
    {
        builder.PushLine(std::format(".method {} final {} {} {}({}) cil managed", AccessModifierString(this), StaticModifierString(this), creationType->FullName(), name, ScopedParameterString(this)));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 0;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        TranspileScope(scope, innerBuilder, maxSlotSize);

        builder.PushLine(std::format(".maxstack {}", maxSlotSize));
        ScopedLocalVariableString(this, builder);

        builder.Push(innerBuilder.Value());

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    GeneratedGetFunction::GeneratedGetFunction(const Enums::Describer describer, std::string variableName, const IDataType* const creationType) : MethodDefinition("__get__" + variableName, describer, creationType), variableName(std::move(variableName))
    { }

    MemberType GeneratedGetFunction::MemberType() const { return MemberType::MethodDefinition; }

    const std::string& GeneratedGetFunction::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} {} {} get_{}::{}()",  CheckDescriber(Describer::Static) ? "call" : "callvirt instance", creationType->MemberType() == MemberType::Class ? "class" : "valuetype", creationType->FullName(), parent->FullName(), name);

        return fullName;
    }

    unsigned long GeneratedGetFunction::ParameterCount() const { return 0; }

    const IDataType* GeneratedGetFunction::ParameterAt(const unsigned long index) const
    { return nullptr; }

    void GeneratedGetFunction::BindLocal()
    { }

    void GeneratedGetFunction::Transpile(StringBuilder& builder) const
    {
        builder.PushLine(std::format(".method {} final {} void {}() cil managed", AccessModifierString(this), StaticModifierString(this), name));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        builder.PushLine(std::string_view(".maxstack 1"));
        builder.PushLine(load_this);
        builder.PushLine(std::format("ld{}fld {} {}", CheckDescriber(Describer::Static) ? "s" : "", creationType->FullName(), parent->FindCharacteristic(variableName)->FullName()));
        builder.PushLine(ret);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    BuiltInMethod::BuiltInMethod(const std::string& name, const Enums::Describer describer, const IDataType* const creationType, const std::string& instruction) : MethodDefinition(name, describer, creationType), BuiltInFunction()
    {
        fullName = instruction;
    }

    MemberType BuiltInMethod::MemberType() const { return MemberType::BuiltInDefinition; }

    const std::string& BuiltInMethod::FullName() const { return fullName; }

    void BuiltInMethod::BindLocal()
    { }

    void BuiltInMethod::Transpile(StringBuilder& builder) const
    { }
}
