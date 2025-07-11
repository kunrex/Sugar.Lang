#include "void_function.h"

#include <format>

#include "../../Local/Scopes/scope.h"

#include "../../Core/DataTypes/data_type.h"

#include "../../../Creation/Binding/local_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

using namespace Services;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    VoidFunction::VoidFunction(const std::string& name, const Enums::Describer describer, const IParseNode* const body) : VoidDefinition(name, describer), Scoped(body)
    { }

    MemberType VoidFunction::MemberType() const { return MemberType::VoidDefinition; }

    const std::string& VoidFunction::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} void {}::{}{}",  CheckDescriber(Describer::Static) ? "call" : "callvirt instance", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    void VoidFunction::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);
        scope->Print("", true);
    }

    void VoidFunction::Transpile(StringBuilder& builder) const
    {
        builder.PushLine(std::format(".method {} final {} void {}({}) cil managed", AccessModifierString(this), StaticModifierString(this), name, ScopedParameterString(this)));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 0;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        TranspileScope(scope, innerBuilder, maxSlotSize);

        builder.PushLine(std::format(".maxstack {}", maxSlotSize));
        ScopedLocalVariableString(this, builder);

        builder.Push(innerBuilder.Value());
        builder.PushLine(ret);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    Entrypoint::Entrypoint(const std::string& name, const Enums::Describer describer, const IParseNode* const body) : VoidFunction(name, describer, body)
    { }

    Entrypoint* Entrypoint::instance = nullptr;

    const Entrypoint* Entrypoint::Instance() { return instance; }

    Entrypoint* Entrypoint::InitInstance(const std::string& name, const Enums::Describer describer, const IParseNode* const body)
    {
        if (instance == nullptr)
            instance = new Entrypoint(name, describer, body);

        return instance;
    }

    void Entrypoint::Transpile(StringBuilder& builder) const
    {
        builder.PushLine(std::format(".method {} final {} void {}({}) cil managed", AccessModifierString(this), StaticModifierString(this), name, ScopedParameterString(this)));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 0;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        TranspileScope(scope, innerBuilder, maxSlotSize);

        builder.PushLine(std::string_view(".entrypoint"));
        builder.PushLine(std::format(".maxstack {}", maxSlotSize));
        ScopedLocalVariableString(this, builder);

        builder.Push(innerBuilder.Value());
        builder.PushLine(ret);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    GeneratedSetFunction::GeneratedSetFunction(const Enums::Describer describer, std::string variableName, const IDataType* const creationType) : VoidDefinition("__set__" + variableName, describer), variableName(std::move(variableName)), creationType(creationType)
    { }

    MemberType GeneratedSetFunction::MemberType() const { return MemberType::VoidDefinition; }

    const std::string& GeneratedSetFunction::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} void {}::{}({})", CheckDescriber(Describer::Static) ? "call" : "callvirt instance", parent->FullName(), name, creationType->FullName());

        return fullName;
    }

    unsigned long GeneratedSetFunction::ParameterCount() const { return 1; }
    const IDataType* GeneratedSetFunction::ParameterAt(const unsigned long index) const
    {
        if (index == 0)
            return creationType;

        return nullptr;
    }

    void GeneratedSetFunction::BindLocal()
    { }

    void GeneratedSetFunction::Transpile(StringBuilder& builder) const
    {
        builder.PushLine(std::format(".method {} final {} void {}({} value) cil managed", AccessModifierString(this), StaticModifierString(this), name, creationType->FullName()));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        builder.PushLine(std::string_view(".maxstack 2"));
        builder.PushLine(load_this);
        builder.PushLine(std::string_view("ldarg.1"));
        builder.PushLine(std::format("st{}fld {} {}", CheckDescriber(Describer::Static) ? "s" : "", creationType->FullName(), parent->FindCharacteristic(variableName)->FullName()));
        builder.PushLine(ret);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    BuiltInVoid::BuiltInVoid(const std::string& name, const Enums::Describer describer, const std::string& instruction) : VoidDefinition(name, describer), BuiltInFunction()
    {
        fullName = instruction;
    }

    MemberType BuiltInVoid::MemberType() const { return MemberType::BuiltInDefinition; }

    const std::string& BuiltInVoid::FullName() const { return fullName; }

    void BuiltInVoid::BindLocal()
    { }

    void BuiltInVoid::Transpile(StringBuilder& builder) const
    { }
}

