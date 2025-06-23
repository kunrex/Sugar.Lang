#include "boolean.h"

#include "long.h"
#include "integer.h"
#include "short.h"
#include "built_in_functions.h"

#include "../Reference/string.h"

#include "../../Compilation/compilation_result.h"

#include "../../DataTypes/data_type_extensions.h"

#include "../../Global/Functions/cast_overload.h"
#include "../../Global/Functions/method_function.h"
#include "../../Global/Functions/operator_overload.h"
#include "../Generic/referenced.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

namespace
{
    CompilationResult Not(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Boolean::Instance(), !std::get<bool>(arguments[0].data)} ; }

    CompilationResult And(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Boolean::Instance(), std::get<bool>(arguments[0].data) && std::get<bool>(arguments[1].data)}; }
    CompilationResult Or(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Boolean::Instance(), std::get<bool>(arguments[0].data) || std::get<bool>(arguments[1].data)}; }
}

namespace Analysis::Structure::Wrappers
{
    Boolean::Boolean() : BuiltInValueType("bool", Enums::Describer::Public), SingletonService()
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
        const auto tryParse = new BuiltInMethod("TryParse", Enums::Describer::PublicStatic, this, "bool valuetype [System.Runtime]System.Boolean::TryParse(string, bool&)");
        tryParse->PushParameterType(String::Instance());
        tryParse->PushParameterType(Referenced::Instance(this));
        functions[0] = { ArgumentHash(tryParse), tryParse };

        const auto getHash = GetHash();
        functions[1] = { ArgumentHash(getHash), getHash };

        const auto explicitShort = new BuiltInCast(Short::Instance(), "conv.i2", ShortCast<bool>);
        explicitShort->PushParameterType(this);
        explicitCasts[0] = { ArgumentHash({ Short::Instance(), this}), explicitShort };

        const auto explicitInteger = new BuiltInCast(Integer::Instance(), "conv.i4", IntCast<bool>);
        explicitInteger->PushParameterType(this);
        explicitCasts[1] = { ArgumentHash({ Integer::Instance(), this }), explicitInteger };

        const auto explicitLong = new BuiltInCast(Long::Instance(), "conv.i8", LongCast<bool>);
        explicitLong->PushParameterType(this);
        explicitCasts[2] = { ArgumentHash({ Long::Instance(), this }), explicitLong };

        const auto explicitString = new BuiltInCast(String::Instance(), "call instance string valuetype [System.Runtime]System.Boolean::ToString()", StringCast<bool>);
        explicitString->PushParameterType(this);
        explicitCasts[3] = { ArgumentHash({ String::Instance(), this }), explicitString };

        const auto equals = new BuiltInOverload(SyntaxKind::Equals, this, "ceq", Equals<bool>);
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads[0] = { SyntaxKind::Equals, equals };

        const auto notEquals = new BuiltInOverload(SyntaxKind::NotEquals, this, "ceq ldc.i4.0 ceq", NotEquals<bool>);
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads[1] = { SyntaxKind::NotEquals, notEquals };

        const auto logicalNot = new BuiltInOverload(SyntaxKind::Not, this, "ldc.i4.0 ceq", Not);
        logicalNot->PushParameterType(this);
        overloads[2] = { SyntaxKind::Not, logicalNot };

        const auto logicalAnd = new BuiltInOverload(SyntaxKind::And, this, "and", And);
        logicalAnd->PushParameterType(this);
        logicalAnd->PushParameterType(this);
        overloads[3] = { SyntaxKind::And, logicalAnd };

        const auto logicalOr = new BuiltInOverload(SyntaxKind::Or, this, "or", Or);
        logicalOr->PushParameterType(this);
        logicalOr->PushParameterType(this);
        overloads[4] = { SyntaxKind::Or, logicalOr };
    }

    const ICharacteristic* Boolean::FindCharacteristic(const string& name) const
    { return nullptr; }

    const IFunctionDefinition* Boolean::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) & ArgumentHash(argumentList);

        for (const auto function: functions)
            if (function.first == hash)
                return function.second;

        return nullptr;
    }

    const IConstructor* Boolean::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Boolean::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Boolean::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Boolean::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        return FindBuiltInCast(returnType, fromType);
    }

    const IBuiltInCast* Boolean::FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });

        for (const auto cast: explicitCasts)
            if (cast.first == hash)
                return cast.second;

        return nullptr;
    }

    const IOperatorOverload* Boolean::FindOverload(const SyntaxKind base) const
    {
        return FindBuiltInOverload(base);
    }

    const IBuiltInOverload* Boolean::FindBuiltInOverload(const SyntaxKind base) const
    {
        for (const auto overload: overloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    Boolean::~Boolean()
    {
        for (const auto function: functions)
            delete function.second;

        for (const auto cast: explicitCasts)
            delete cast.second;

        for (const auto overload: overloads)
            delete overload.second;
    }
}
