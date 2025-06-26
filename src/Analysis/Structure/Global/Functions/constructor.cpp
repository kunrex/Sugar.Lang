#include "constructor.h"

#include <format>

#include "../../Core/DataTypes/data_type.h"

#include "../../../Creation/Binding/local_binder.h"
#include "../../../Creation/Transpiling/cil_transpiler.h"

using namespace Services;

using namespace ParseNodes;
using namespace ParseNodes::Groups;
using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

const auto defaultConstructor = Tokens::Token(0, Tokens::Enums::TokenType::Constant, Tokens::Enums::SyntaxKind::Constant, 0.0);

namespace Analysis::Structure::Global
{
    ConstructorDefinition::ConstructorDefinition(const Enums::Describer describer, const IDataType* const creationType) : Function(describer, creationType)
    { }

    Constructor::Constructor(const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : Nameable(".ctor"), ConstructorDefinition(describer, creationType), Scoped(body)
    { }

    MemberType Constructor::MemberType() const { return MemberType::Constructor; }

    const std::string& Constructor::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("instance void {}::.ctor{}", parent->FullName(), ParameterString(this));

        return fullName;
    }

    void Constructor::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);
    }

    void Constructor::Transpile(StringBuilder& builder) const
    {
        builder.PushLine(std::format(".method {} final hidebysig specialname rtspecialname instance void .ctor({}) cil managed", AccessModifierString(this), ScopedParameterString(this)));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 1;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        parent->InstanceConstructor()->PushTranspilation(innerBuilder, maxSlotSize);
        TranspileScope(scope, innerBuilder, maxSlotSize);

        builder.PushLine(std::format(".maxstack {}", maxSlotSize));
        ScopedLocalVariableString(this, builder);

        if (parent->MemberType() == MemberType::Class)
        {
            builder.PushLine(load_this);
            builder.PushLine(std::string_view("call instance void [System.Runtime]System.Object::.ctor()"));
        }

        builder.Push(innerBuilder.Value());
        builder.PushLine(ret);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    void Constructor::PushTranspilation(const ICharacteristic* const characteristic)
    { }

    void Constructor::PushTranspilation(StringBuilder& builder, int& slotSize) const
    { }

    ImplicitConstructor::ImplicitConstructor(const Enums::Describer describer, const IDataType* const creationType) : ConstructorDefinition(describer, creationType)
    { }

    MemberType ImplicitConstructor::MemberType() const { return MemberType::GeneratedConstructor; }

    const std::string& ImplicitConstructor::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("instance void {}::.ctor()", parent->FullName());

        return fullName;
    }

    unsigned long ImplicitConstructor::ParameterCount() const { return 0; }

    const IDataType* ImplicitConstructor::ParameterAt(const unsigned long index) const
    { return nullptr; }

    void ImplicitConstructor::BindLocal()
    { }

    void ImplicitConstructor::Transpile(StringBuilder& builder) const
    {
        builder.PushLine(std::format(".method {} final hidebysig specialname rtspecialname instance void .ctor() cil managed", AccessModifierString(this)));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 1;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        PushTranspilation(innerBuilder, maxSlotSize);

        builder.PushLine(std::format(".maxstack {}", maxSlotSize));

        if (parent->MemberType() == MemberType::Class)
        {
            builder.PushLine(load_this);
            builder.PushLine(std::string_view("call instance void [System.Runtime]System.Object::.ctor()"));
        }

        builder.Push(innerBuilder.Value());
        builder.PushLine(ret);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    void ImplicitConstructor::PushTranspilation(const ICharacteristic* const characteristic) { characteristics.push_back(characteristic); }

    void ImplicitConstructor::PushTranspilation(StringBuilder& builder, int& slotSize) const
    {
        for (const auto characteristic : characteristics)
        {
            const auto context = characteristic->Context();

            builder.PushLine(load_this);
            TranspileExpression(context, builder);
            builder.PushLine(std::format("stfld {} {}", characteristic->CreationType()->FullName(), characteristic->FullName()));

            slotSize = std::max(slotSize, context->SlotCount());
        }
    }

    StaticImplicitConstructor::StaticImplicitConstructor(const IDataType* const creationType) : ConstructorDefinition(Describer::Private | Describer::Static, creationType)
    { }

    MemberType StaticImplicitConstructor::MemberType() const { return MemberType::GeneratedConstructor; }

    const std::string& StaticImplicitConstructor::FullName() const { return fullName; }

    unsigned long StaticImplicitConstructor::ParameterCount() const { return 0; }

    const IDataType* StaticImplicitConstructor::ParameterAt(const unsigned long index) const
    { return nullptr; }

    void StaticImplicitConstructor::BindLocal()
    { }

    void StaticImplicitConstructor::Transpile(StringBuilder& builder) const
    {
        if (characteristics.empty())
            return;

        builder.PushLine(std::string_view(".method private specialname rtspecialname static void .cctor() cil managed"));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 1;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        PushTranspilation(innerBuilder, maxSlotSize);

        builder.PushLine(std::format(".maxstack {}", maxSlotSize));

        builder.Push(innerBuilder.Value());
        builder.PushLine(ret);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    void StaticImplicitConstructor::PushTranspilation(const ICharacteristic* const characteristic) { characteristics.push_back(characteristic); }

    void StaticImplicitConstructor::PushTranspilation(StringBuilder& builder, int& slotSize) const
    {
        for (const auto characteristic : characteristics)
        {
            const auto context = characteristic->Context();

            TranspileExpression(context, builder);
            builder.PushLine(std::format("stsfld {} {}", characteristic->CreationType()->FullName(), characteristic->FullName()));

            slotSize = std::max(slotSize, context->SlotCount());
        }
    }

    DefinedConstructor::DefinedConstructor(const Enums::Describer describer, const IDataType* const creationType, const IParseNode* const body) : Nameable(".ctor"), ConstructorDefinition(describer, creationType), Scoped(body)
    { }

    MemberType DefinedConstructor::MemberType() const { return MemberType::Constructor; }

    const std::string& DefinedConstructor::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = std::format("instance void {}::.ctor{}", parent->FullName(), ParameterString(this));

        return fullName;
    }

    void DefinedConstructor::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);
    }

    void DefinedConstructor::Transpile(StringBuilder& builder) const
    {
        builder.PushLine(std::format(".method {} final hidebysig specialname rtspecialname instance void .ctor({}) cil managed", AccessModifierString(this), ScopedParameterString(this)));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 2;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        PushTranspilation(innerBuilder, maxSlotSize);
        TranspileScope(scope, innerBuilder, maxSlotSize);

        builder.PushLine(std::format(".maxstack {}", maxSlotSize));
        ScopedLocalVariableString(this, builder);

        if (parent->MemberType() == MemberType::Class)
        {
            builder.PushLine(load_this);
            builder.PushLine(std::string_view("call instance void [System.Runtime]System.Object::.ctor()"));
        }

        builder.Push(innerBuilder.Value());
        builder.PushLine(ret);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    void DefinedConstructor::PushTranspilation(const ICharacteristic* characteristic) { characteristics.push_back(characteristic); }

    void DefinedConstructor::PushTranspilation(StringBuilder& builder, int& slotSize) const
    {
        for (const auto characteristic : characteristics)
        {
            const auto context = characteristic->Context();

            builder.PushLine(load_this);
            TranspileExpression(context, builder);
            builder.PushLine(std::format("stfld {} {}", characteristic->CreationType()->FullName(), characteristic->FullName()));

            slotSize = std::max(slotSize, context->SlotCount());
        }
    }

    StaticDefinedConstructor::StaticDefinedConstructor(const IDataType* const creationType, const IParseNode* const body) : Nameable(".cctor"), ConstructorDefinition(Describer::Private | Describer::Static, creationType), Scoped(body)
    { }

    MemberType StaticDefinedConstructor::MemberType() const { return MemberType::Constructor; }

    const std::string& StaticDefinedConstructor::FullName() const { return name; }

    void StaticDefinedConstructor::BindLocal()
    {
        BindScope(parseNode, scope, this, parent);
    }

    void StaticDefinedConstructor::Transpile(StringBuilder& builder) const
    {
        builder.PushLine(std::string_view(".method private specialname rtspecialname static void .cctor() cil managed"));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        int maxSlotSize = 1;

        auto innerBuilder = StringBuilder();
        innerBuilder.SetIndent(builder.Indent());

        PushTranspilation(innerBuilder, maxSlotSize);
        TranspileScope(scope, innerBuilder, maxSlotSize);

        builder.PushLine(std::format(".maxstack {}", maxSlotSize));
        ScopedLocalVariableString(this, builder);

        builder.Push(innerBuilder.Value());
        builder.PushLine(ret);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    void StaticDefinedConstructor::PushTranspilation(const ICharacteristic* const characteristic) { characteristics.push_back(characteristic); }

    void StaticDefinedConstructor::PushTranspilation(StringBuilder& builder, int& slotSize) const
    {
        for (const auto characteristic : characteristics)
        {
            const auto context = characteristic->Context();

            TranspileExpression(context, builder);
            builder.PushLine(std::format("stsfld {} {}", characteristic->CreationType()->FullName(), characteristic->FullName()));

            slotSize = std::max(slotSize, context->SlotCount());
        }
    }

    BuiltInConstructor::BuiltInConstructor(const IDataType* const creationType, const std::string& instruction) : ConstructorDefinition(Describer::Public, creationType), BuiltInFunction()
    {
        fullName = instruction;
    }

    MemberType BuiltInConstructor::MemberType() const { return MemberType::GeneratedConstructor; }

    const std::string& BuiltInConstructor::FullName() const { return fullName; }

    void BuiltInConstructor::BindLocal()
    { }

    void BuiltInConstructor::Transpile(StringBuilder& builder) const
    { }

    void BuiltInConstructor::PushTranspilation(const ICharacteristic* const characteristic)
    { }

    void BuiltInConstructor::PushTranspilation(StringBuilder& builder, int& slotSize) const
    { }
}

