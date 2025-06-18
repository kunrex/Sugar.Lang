#include "enum.h"

#include <format>

#include "data_type_extensions.h"

#include "../../Creation/Binding/global_binder.h"
#include "../../Creation/Binding/binder_extensions.h"

#include "../../../Exceptions/Compilation/Analysis/Global/invalid_global_statement_exception.h"
#include "../../Creation/Transpiling/cil_transpiler.h"
#include "../Global/BuiltIn/built_in_cast.h"
#include "../Global/BuiltIn/built_in_operation.h"
#include "../Wrappers/Generic/action.h"
#include "../Wrappers/Value/integer.h"

#include "../Compilation/compilation_result.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Creation::Binding;
using namespace Analysis::Creation::Transpiling;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

namespace
{
    CompilationResult Not(const std::vector<CompilationResult>& arguments) { return { Integer::Instance(), ~std::get<int>(arguments[0].data)} ; }
    CompilationResult BitwiseAnd(const std::vector<CompilationResult>& arguments) { return { Integer::Instance(), std::get<int>(arguments[0].data) & std::get<int>(arguments[1].data)} ; }
    CompilationResult BitwiseOr(const std::vector<CompilationResult>& arguments) { return { Integer::Instance(), std::get<int>(arguments[0].data) | std::get<int>(arguments[1].data)} ; }
    CompilationResult RightShift(const std::vector<CompilationResult>& arguments) { return { Integer::Instance(), std::get<int>(arguments[0].data) >> std::get<int>(arguments[1].data)} ; }
    CompilationResult LeftShift(const std::vector<CompilationResult>& arguments) { return { Integer::Instance(), std::get<int>(arguments[0].data) << std::get<int>(arguments[1].data)} ; }
    CompilationResult BitwiseXor(const std::vector<CompilationResult>& arguments) { return { Integer::Instance(), std::get<int>(arguments[0].data) ^ std::get<int>(arguments[1].data)} ; }
}

namespace Analysis::Structure::DataTypes
{
    Enum::Enum(const string& name, const Enums::Describer describer, const IParseNode* skeleton) : DataType(name, describer | Describer::Static), skeleton(skeleton), fullName(), explicitCasts()
    { }

    MemberType Enum::MemberType() const { return MemberType::Enum; }

    int Enum::SlotCount() const { return 1; }

    TypeKind Enum::Type() const { return TypeKind::Custom; }

    const string& Enum::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    const ICharacteristic* Enum::LastCharacteristic() const
    {
        if (characteristics.empty())
            return nullptr;

        return characteristics[characteristics.size() - 1];
    }

    void Enum::PushCharacteristic(ICharacteristic* const characteristic)
    {
        characteristics.push_back(characteristic);
    }

    const ICharacteristic* Enum::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    void Enum::PushFunction(IFunctionDefinition* const function)
    { }

    const IFunctionDefinition* Enum::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr;}

    void Enum::PushConstructor(IConstructor* constructor)
    { }

    const IConstructor* Enum::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        return nullptr;
    }

    IConstructor* Enum::StaticConstructor() const { return nullptr; }
    IConstructor* Enum::InstanceConstructor() const { return nullptr; }

    void Enum::PushIndexer(IIndexerDefinition* const indexer)
    { }

    const IIndexerDefinition* Enum::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        return nullptr;
    }

    void Enum::PushImplicitCast(IFunction* const cast)
    { }

    const IFunction* Enum::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        return nullptr;
    }

    void Enum::PushExplicitCast(IFunction* const cast)
    {
        explicitCasts.emplace_back(ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)})), cast);
    }

    const IFunction* Enum::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));

        for (const auto cast : explicitCasts)
            if (std::get<0>(cast) == hash)
                return std::get<1>(cast);

        return nullptr;
    }

    void Enum::PushOverload(IOperatorOverload* const overload)
    { }

    const IOperatorOverload* Enum::FindOverload(const SyntaxKind base) const
    {
        for (const auto overload : overloads)
            if (std::get<0>(overload) == base)
                return std::get<1>(overload);

        return nullptr;
    }

    void Enum::BindGlobal()
    {
        const auto count = skeleton->ChildCount();
        for (auto i = 0; i < count; i++)
            BindEnumConstant(skeleton->GetChild(i), this);

        const auto explicitInteger = new BuiltInCast(Integer::Instance(), "conv.i4", nullptr);
        explicitInteger->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash(explicitInteger), explicitInteger);

        const auto explicitString = new BuiltInCast(Integer::Instance(), std::format("box {} callvirt instance string [System.Runtime]System.Enum::ToString()", fullName), nullptr);
        explicitString->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash(explicitString), explicitString);

        const auto bitwiseNot = new BuiltInOperation(SyntaxKind::BitwiseNot, this, "not", Not);
        bitwiseNot->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::BitwiseNot, bitwiseNot);

        const auto bitwiseAnd = new BuiltInOperation(SyntaxKind::BitwiseAnd, this, "and", BitwiseAnd);
        bitwiseAnd->PushParameterType(this);
        bitwiseAnd->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::BitwiseAnd, bitwiseAnd);

        const auto bitwiseOr = new BuiltInOperation(SyntaxKind::BitwiseOr, this, "or", BitwiseOr);
        bitwiseOr->PushParameterType(this);
        bitwiseOr->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::BitwiseOr, bitwiseOr);

        const auto bitwiseXor = new BuiltInOperation(SyntaxKind::BitwiseXor, this, "xor", BitwiseXor);
        bitwiseXor->PushParameterType(this);
        bitwiseXor->PushParameterType(Integer::Instance());
        overloads.emplace_back(SyntaxKind::BitwiseXor, bitwiseXor);

        const auto rightShift = new BuiltInOperation(SyntaxKind::RightShift, this, "shr", RightShift);
        rightShift->PushParameterType(this);
        rightShift->PushParameterType(Integer::Instance());
        overloads.emplace_back(SyntaxKind::RightShift, rightShift);

        const auto leftShift = new BuiltInOperation(SyntaxKind::LeftShift, this, "shl", LeftShift);
        leftShift->PushParameterType(this);
        leftShift->PushParameterType(Integer::Instance());
        overloads.emplace_back(SyntaxKind::LeftShift, leftShift);
    }

    void Enum::BindLocal()
    {
        for (const auto characteristic : characteristics)
            characteristic->BindLocal();
    }

    void Enum::Transpile(Services::StringBuilder& builder) const
    {
        builder.PushLine();
        builder.PushLine(std::format(".class {} sealed auto ansi {} extends [System.Runtime]System.Enum", AccessModifierString(this), fullName));

        builder.PushLine(open_flower);
        builder.IncreaseIndent();

        builder.PushLine(".field public specialname rtspecialname int32 value__ ");

        for (const auto characteristic : characteristics)
            characteristic->Transpile(builder);

        builder.DecreaseIndent();
        builder.PushLine(close_flower);
    }

    void Enum::Print(const string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Enum: " << name << std::endl;
    }

    Enum::~Enum()
    {
        for (const auto characteristic : characteristics)
            delete characteristic;

        for (const auto cast: explicitCasts)
            delete std::get<1>(cast);

        for (const auto overload: overloads)
            delete std::get<1>(overload);
    }
}
