#include "void_function.h"

#include <format>

#include "function_extensions.h"

#include "../../Core/DataTypes/data_type.h"

#include "../../../Creation/Binding/local_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

using namespace std;

using namespace Services;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Global
{
    VoidFunction::VoidFunction(const string& name, const Enums::Describer describer, const IParseNode* const body) : VoidDefinition(name, describer), Scoped(body)
    { }

    MemberType VoidFunction::MemberType() const { return MemberType::VoidDefinition; }

    const string& VoidFunction::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} void {} {}::{}{}",  CheckDescriber(Describer::Static) ? "" : "instance", parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, ParameterString(this));

        return fullName;
    }

    void VoidFunction::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);
    }

    void VoidFunction::Transpile(StringBuilder& builder) const
    {
        builder.PushLine("");
        builder.PushLine(std::format(".method {} final {} void {}({}) cil managed", AccessModifierString(this), StaticModifierString(this), name, ScopedParameterString(this)));

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

    Entrypoint::Entrypoint(const std::string& name, const Enums::Describer describer, const IParseNode* const body) : VoidFunction(name, describer, body)
    { }

    const Entrypoint* Entrypoint::Instance() { return instance; }

    Entrypoint* Entrypoint::InitInstance(const std::string& name, const Enums::Describer describer, const IParseNode* const body)
    {
        if (instance == nullptr)
            instance = new Entrypoint(name, describer, body);

        return instance;
    }

    void Entrypoint::Transpile(StringBuilder& builder) const
    {
        builder.PushLine("");
        builder.PushLine(std::format(".method {} final {} void {}({}) cil managed", AccessModifierString(this), StaticModifierString(this), name, ScopedParameterString(this)));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 0;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        TranspileScope(scope, innerBuilder, maxSlotSize);

        builder.PushLine(".entrypoint");
        builder.PushLine(std::format(".maxstack {}", maxSlotSize));
        builder.PushLine(std::format(".localsinit({})", ScopedLocalVariableString(this)));

        builder.Push(innerBuilder.Value());

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    GeneratedSetFunction::GeneratedSetFunction(const Enums::Describer describer, std::string name, const IDataType* const creationType) : VoidDefinition("__set__" + name, describer), DefaultScoped(), name(std::move(name)), creationType(creationType)
    { }

    MemberType GeneratedSetFunction::MemberType() const { return MemberType::VoidDefinition; }

    const std::string& GeneratedSetFunction::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} void {} {}::{}({})",  CheckDescriber(Describer::Static) ? "" : "instance", parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), name, creationType->FullName());

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
        builder.PushLine("");
        builder.PushLine(std::format(".method {} final {} void {}({} value) cil managed", AccessModifierString(this), StaticModifierString(this), name, creationType()->FullName()));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        builder.PushLine(".maxstack 2");
        builder.PushLine(load_this);
        builder.PushLine("ldarg.1");
        builder.PushLine(std::format("st{}fld {} {}", CheckDescriber(Describer::Static) ? "s" : "", creationType()->FullName(), parent->FindCharacteristic(name)->FullName()));
        builder.PushLine("ret");

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }
}

