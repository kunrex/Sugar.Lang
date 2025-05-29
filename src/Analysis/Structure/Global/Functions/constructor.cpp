#include "constructor.h"

#include <format>

#include "function_extensions.h"

#include "../../Core/DataTypes/data_type.h"

#include "../../../Creation/Binding/local_binder.h"

#include "../../../../Parsing/ParseNodes/Groups/scope_node.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

using namespace std;

using namespace Services;

using namespace ParseNodes;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Creation::Binding;
using namespace Analysis::Structure::Core::Interfaces;

const auto defaultConstructor = Tokens::Token(0, Tokens::Enums::TokenType::Constant, Tokens::Enums::SyntaxKind::Constant, 0.0);

namespace Analysis::Structure::Global
{
    Constructor::Constructor(const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : Nameable(".ctor"), ConstructorDefinition(describer, creationType), Scoped(body)
    { }

    MemberType Constructor::MemberType() const { return MemberType::Constructor; }

    const string& Constructor::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} instance void {} {}::.ctor{}", creationType->MemberType() == MemberType::Class ? "newobj" : "call", parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), ParameterString(this));

        return fullName;
    }

    void Constructor::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);
    }

    void Constructor::Transpile(StringBuilder& builder) const
    {
        builder.PushLine("");
        builder.PushLine(std::format(".method {} final hidebysig specialname rtspecialname instance void .ctor({}) cil managed", AccessModifierString(this), ScopedParameterString(this)));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 1;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        TranspileScope(scope, innerBuilder, maxSlotSize);

        builder.PushLine(".maxstack " + maxSlotSize);
        builder.PushLine(std::format(".localsinit({})", ScopedLocalVariableString(this)));

        builder.PushLine(load_this);
        builder.PushLine("call instance void [System.Runtime]System.Object::.ctor()");

        parent->InstanceConstructor()->Transpile(builder);
        builder.Push(innerBuilder.Value());

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    void Constructor::PushTranspilation(StringBuilder& builder) const
    { }

    void Constructor::PushTranspilation(const ICharacteristic* const characteristic)
    { }

    ImplicitConstructor::ImplicitConstructor(const Enums::Describer describer, const IDataType* const creationType) : Nameable(".ctor"), ConstructorDefinition(describer, creationType), DefaultScoped(), characteristics()
    { }

    MemberType ImplicitConstructor::MemberType() const { return MemberType::Constructor; }

    const std::string& ImplicitConstructor::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} instance void {} {}::.ctor{}", creationType->MemberType() == MemberType::Class ? "newobj" : "call", parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), ParameterString(this));

        return fullName;
    }

    void ImplicitConstructor::BindLocal()
    { }

    void ImplicitConstructor::Transpile(StringBuilder& builder) const
    {
        builder.PushLine("");
        builder.PushLine(std::format(".method {} final hidebysig specialname rtspecialname instance void .ctor() cil managed", AccessModifierString(this)));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        builder.PushLine(".maxstack 1");
        builder.PushLine(load_this);
        builder.PushLine("call instance void [System.Runtime]System.Object::.ctor()");

        PushTranspilation(builder);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    void ImplicitConstructor::PushTranspilation(StringBuilder& builder) const
    {
        if (!characteristics.empty())
        {
            for (const auto characteristic: characteristics)
            {
                builder.PushLine(load_this);
                TranspileExpression(characteristic->Context(), builder);
                builder.PushLine(std::format("stfld {} {}", characteristic->CreationType()->FullName(), characteristic->FullName()));
            }
        }
    }

    void ImplicitConstructor::PushTranspilation(const ICharacteristic* const characteristic) { characteristics.push_back(characteristic); }

    StaticImplicitConstructor::StaticImplicitConstructor(const IDataType* const creationType) : Nameable(".cctor"), ConstructorDefinition(Describer::Private | Describer::Static, creationType), DefaultScoped(), characteristics()
    { }

    MemberType StaticImplicitConstructor::MemberType() const { return MemberType::Constructor; }

    const std::string& StaticImplicitConstructor::FullName() const { return name; }

    void StaticImplicitConstructor::BindLocal()
    { }

    void StaticImplicitConstructor::Transpile(StringBuilder& builder) const
    {
        if (characteristics.empty())
            return;

        builder.PushLine();
        builder.PushLine(".method private specialname rtspecialname static void .cctor() cil managed");

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        builder.PushLine(".maxstack 1");

        for (const auto characteristic: characteristics)
        {
            TranspileExpression(characteristic->Context(), builder);
            builder.PushLine(std::format("stsfld {} {}", characteristic->CreationType()->FullName(), characteristic->FullName()));
        }

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    void StaticImplicitConstructor::PushTranspilation(StringBuilder& builder) const
    { }

    void StaticImplicitConstructor::PushTranspilation(const ICharacteristic* const characteristic) { characteristics.push_back(characteristic); }

    DefinedConstructor::DefinedConstructor(const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : Nameable(".ctor"), ConstructorDefinition(describer, creationType), Scoped(body), characteristics()
    { }

    MemberType DefinedConstructor::MemberType() const { return MemberType::Constructor; }

    const std::string& DefinedConstructor::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("{} instance void {} {}::.ctor{}", creationType->MemberType() == MemberType::Class ? "newobj" : "call", parent->MemberType() == MemberType::Class ? "class" : "valuetype", parent->FullName(), ParameterString(this));

        return fullName;
    }

    void DefinedConstructor::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);
    }

    void DefinedConstructor::Transpile(StringBuilder& builder) const
    {
        builder.PushLine("");
        builder.PushLine(std::format(".method {} final hidebysig specialname rtspecialname instance void .ctor({}) cil managed", AccessModifierString(this), ScopedParameterString(this)));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 2;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        TranspileScope(scope, innerBuilder, maxSlotSize);

        builder.PushLine(".maxstack " + maxSlotSize);
        builder.PushLine(std::format(".localsinit({})", ScopedLocalVariableString(this)));

        builder.PushLine(load_this);
        builder.PushLine("call instance void [System.Runtime]System.Object::.ctor()");

        PushTranspilation(builder);
        builder.Push(innerBuilder.Value());

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    void DefinedConstructor::PushTranspilation(StringBuilder& builder) const
    {
        if (!characteristics.empty())
        {
            for (const auto characteristic: characteristics)
            {
                builder.PushLine(load_this);
                TranspileExpression(characteristic->Context(), builder);
                builder.PushLine(std::format("stfld {} {}", characteristic->CreationType()->FullName(), characteristic->FullName()));
            }
        }
    }

    void DefinedConstructor::PushTranspilation(const ICharacteristic* characteristic) { characteristics.push_back(characteristic); }

    StaticDefinedConstructor::StaticDefinedConstructor(const IDataType* const creationType, const IParseNode* const body) : Nameable(".cctor"), ConstructorDefinition(Describer::Private | Describer::Static, creationType), Scoped(body), characteristics()
    { }

    MemberType StaticDefinedConstructor::MemberType() const { return MemberType::Constructor; }

    const std::string& StaticDefinedConstructor::FullName() const { return name; }

    void StaticDefinedConstructor::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);
    }

    void StaticDefinedConstructor::Transpile(StringBuilder& builder) const
    {
        builder.PushLine();
        builder.PushLine(".method private specialname rtspecialname static void .cctor() cil managed");

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 1;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        TranspileScope(scope, innerBuilder, maxSlotSize);

        builder.PushLine(".maxstack " + maxSlotSize);

        if (!characteristics.empty())
        {
            for (const auto characteristic: characteristics)
            {
                TranspileExpression(characteristic->Context(), builder);
                builder.PushLine(std::format("stsfld {} {}", characteristic->CreationType()->FullName(), characteristic->FullName()));
            }
        }

        builder.Push(innerBuilder.Value());

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    void StaticDefinedConstructor::PushTranspilation(StringBuilder& builder) const
    { }

    void StaticDefinedConstructor::PushTranspilation(const ICharacteristic* const characteristic) { characteristics.push_back(characteristic); }
}

