#include "boolean.h"

#include "built_in_functions.h"
#include "../../DataTypes/data_type_extensions.h"

#include "long.h"
#include "integer.h"
#include "short.h"
#include "../Reference/string.h"

#include "../../Compilation/compilation_result.h"

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_operation.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_boolean = "[System.Runtime]System.Boolean";

namespace
{
    CompilationResult Not(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Boolean::Instance(), !std::get<bool>(arguments[0].data)} ; }

    CompilationResult And(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Boolean::Instance(), std::get<bool>(arguments[0].data) && std::get<bool>(arguments[1].data)}; }
    CompilationResult Or(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Boolean::Instance(), std::get<bool>(arguments[0].data) || std::get<bool>(arguments[1].data)}; }
}

namespace Analysis::Structure::Wrappers
{
    Boolean::Boolean() : BuiltInValueType(cil_boolean, Enums::Describer::Public), SingletonService(), implicitCasts(), explicitCasts(), overloads()
    { }

    Boolean Boolean::instance;

    const Boolean* Boolean::Instance() { return &instance; }

    void Boolean::BindGlobalInstance()
    {
        static bool bound;

        if (!bound)
        {
            instance.BindGlobal();
            bound = true;
        }
    }

    int Boolean::SlotCount() const { return 1; }

    TypeKind Boolean::Type() const { return TypeKind::Boolean; }

    void Boolean::BindGlobal()
    {
        const auto explicitShort = new BuiltInCast(Short::Instance(), "conv.i2", ShortCast<bool>);
        explicitShort->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ Short::Instance(), this}), explicitShort);

        const auto explicitInteger = new BuiltInCast(Integer::Instance(), "conv.i4", IntCast<bool>);
        explicitInteger->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ Integer::Instance(), this }), explicitInteger);

        const auto explicitLong = new BuiltInCast(Long::Instance(), "conv.i8", LongCast<bool>);
        explicitLong->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ Long::Instance(), this }), explicitLong);

        const auto explicitString = new BuiltInCast(String::Instance(), "call instance string valuetype [System.Runtime]System.Boolean::ToString()", StringCast<bool>);
        explicitString->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ String::Instance(), this }), explicitString);

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, this, "ceq", Equals<bool>);
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Equals, equals);

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, this, "ceq ldc.i4.0 ceq", NotEquals<bool>);
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::NotEquals, notEquals);

        const auto logicalNot = new BuiltInOperation(SyntaxKind::Not, this, "ldc.i4.0 ceq", Not);
        logicalNot->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Not, logicalNot);

        const auto logicalAnd = new BuiltInOperation(SyntaxKind::And, this, "and", And);
        logicalAnd->PushParameterType(this);
        logicalAnd->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::And, logicalAnd);

        const auto logicalOr = new BuiltInOperation(SyntaxKind::Or, this, "or", Or);
        logicalOr->PushParameterType(this);
        logicalOr->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Or, logicalOr);
    }

    const ICharacteristic* Boolean::FindCharacteristic(const string& name) const
    { return nullptr; }

    const IFunctionDefinition* Boolean::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IConstructor* Boolean::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Boolean::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Boolean::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });

        for (const auto cast: implicitCasts)
            if (std::get<0>(cast) == hash)
                return std::get<1>(cast);

        return nullptr;
    }

    const IFunction* Boolean::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        return FindBuiltInCast(returnType, fromType);
    }

    const IBuiltInCast* Boolean::FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });

        for (const auto cast: explicitCasts)
            if (std::get<0>(cast) == hash)
                return std::get<1>(cast);

        return nullptr;
    }

    const IOperatorOverload* Boolean::FindOverload(const SyntaxKind base) const
    {
        return FindBuiltInOverload(base);
    }

    const IBuiltInOverload* Boolean::FindBuiltInOverload(const SyntaxKind base) const
    {
        for (const auto cast: overloads)
            if (std::get<0>(cast) == base)
                return std::get<1>(cast);

        return nullptr;
    }

    Boolean::~Boolean()
    {
        for (const auto cast: implicitCasts)
            delete std::get<1>(cast);

        for (const auto cast: explicitCasts)
            delete std::get<1>(cast);

        for (const auto overload: overloads)
            delete std::get<1>(overload);
    }
}
