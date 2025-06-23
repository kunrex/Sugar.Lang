#include "double.h"

#include "short.h"
#include "integer.h"
#include "long.h"
#include "./float.h"
#include "boolean.h"
#include "built_in_functions.h"
#include "../Reference/string.h"
#include "../Generic/referenced.h"

#include "../../Compilation/compilation_result.h"
#include "../../Context/Constants/float_constant.h"

#include "../../DataTypes/data_type_extensions.h"

#include "../../Global/Properties/property.h"
#include "../../Global/Functions/cast_overload.h"
#include "../../Global/Functions/method_function.h"
#include "../../Global/Variables/global_constant.h"
#include "../../Global/Functions/operator_overload.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;


namespace
{
    CompilationResult Addition(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Double::Instance(), std::get<double>(arguments[0].data) + std::get<double>(arguments[1].data)} ; }
    CompilationResult Subtraction(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Double::Instance(), std::get<double>(arguments[0].data) - std::get<double>(arguments[1].data)} ; }
    CompilationResult Multiplication(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Double::Instance(), std::get<double>(arguments[0].data) * std::get<double>(arguments[1].data)} ; }
    CompilationResult Division(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Double::Instance(), std::get<double>(arguments[0].data) / std::get<double>(arguments[1].data)} ; }

    CompilationResult Plus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Double::Instance(), arguments[0].data }; }
    CompilationResult Minus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Double::Instance(), -std::get<double>(arguments[0].data) }; }
}

namespace Analysis::Structure::Wrappers
{
    Double::Double() : BuiltInValueType("float64", Describer::Public), SingletonService(), characteristics()
    { }

    Double Double::instance;

    const Double* Double::Instance() { return &instance; }

    void Double::BindGlobalInstance()
    {
        static bool bound;

        if (!bound)
        {
            instance.BindGlobal();
            bound = true;
        }
    }

    int Double::SlotCount() const { return 2; }

    TypeKind Double::Type() const { return TypeKind::Double; }

    void Double::BindGlobal()
    {
        characteristics[0] = new BuiltInConstant("Max", Describer::Public | Describer::Constexpr, this, new DoubleConstant(1.7976931348623157E+308));
        characteristics[1] = new BuiltInConstant("Min", Describer::Public | Describer::Constexpr, this, new DoubleConstant(-1.7976931348623157E+308));

        characteristics[2] = new BuiltInProperty("NaN", Describer::PublicStatic | Describer::Const, this, true, "ldc.r4 NaN", false, "");
        characteristics[3] = new BuiltInProperty("PositiveInfinity", Describer::PublicStatic | Describer::Const, this, true, "ldc.r4 Infinity", false, "");
        characteristics[4] = new BuiltInProperty("NegativeInfinity", Describer::PublicStatic | Describer::Const, this, true, "ldc.r4 -Infinity", false, "");

        characteristics[5] = new BuiltInConstant("Epsilon", Describer::Public | Describer::Constexpr, this, new FloatConstant(4.94065645841247E-324));

        const auto tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, Boolean::Instance(), "call bool [System.Runtime]System.Double::TryParse(string, float64&)");
        tryParse->PushParameterType(String::Instance());
        tryParse->PushParameterType(Referenced::Instance(this));
        functions[0] = { std::hash<string>()(tryParse->Name()) ^ ArgumentHash(tryParse), tryParse };

        const auto getHash = GetHash();
        functions[1] = { std::hash<string>()(getHash->Name()) ^ ArgumentHash(getHash), getHash };

        const auto explicitShort = new BuiltInCast(Short::Instance(), "conv.i2", ShortCast<double>);
        explicitShort->PushParameterType(this);
        explicitCasts[0] = { ArgumentHash({ Short::Instance(), this }), explicitShort };

        const auto explicitInteger = new BuiltInCast(Integer::Instance(), "conv.i4", IntCast<double>);
        explicitInteger->PushParameterType(this);
        explicitCasts[1] = { ArgumentHash({ Integer::Instance(), this }), explicitInteger };

        const auto explicitLong = new BuiltInCast(Long::Instance(), "conv.i8", LongCast<double>);
        explicitLong->PushParameterType(this);
        explicitCasts[2] = { ArgumentHash({ Long::Instance(), this }), explicitLong };

        const auto explicitFloat = new BuiltInCast(Float::Instance(), "conv.r4", FloatCast<double>);
        explicitFloat->PushParameterType(this);
        explicitCasts[3] = { ArgumentHash({ Float::Instance(), this }), explicitFloat };

        const auto explicitString = new BuiltInCast(String::Instance(), "call instance string [System.Runtime]System.Double::ToString()", StringCast<double>);
        explicitString->PushParameterType(this);
        explicitCasts[4] = { ArgumentHash({ String::Instance(), this }), explicitString };

        const auto equals = new BuiltInOverload(SyntaxKind::Equals, Boolean::Instance(), "ceq", Equals<double>);
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        builtInOverloads[0] = { SyntaxKind::Equals, equals };

        const auto notEquals = new BuiltInOverload(SyntaxKind::NotEquals, Boolean::Instance(), "ceq ldc.i4.0 ceq", NotEquals<double>);
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        builtInOverloads[1] = { SyntaxKind::NotEquals, notEquals };

        const auto addition = new BuiltInOverload(SyntaxKind::Addition, this, "add", Addition);
        addition->PushParameterType(this);
        addition->PushParameterType(this);
        builtInOverloads[2] = { SyntaxKind::Addition, addition };

        const auto subtraction = new BuiltInOverload(SyntaxKind::Subtraction, this, "sub", Subtraction);
        subtraction->PushParameterType(this);
        subtraction->PushParameterType(this);
        builtInOverloads[3] = { SyntaxKind::Subtraction, subtraction };

        const auto multiplication = new BuiltInOverload(SyntaxKind::Multiplication,this, "mul", Multiplication);
        multiplication->PushParameterType(this);
        multiplication->PushParameterType(this);
        builtInOverloads[4] = { SyntaxKind::Multiplication, multiplication };

        const auto division = new BuiltInOverload(SyntaxKind::Division, this, "div", Division);
        division->PushParameterType(this);
        division->PushParameterType(this);
        builtInOverloads[5] = { SyntaxKind::Division, division };

        const auto plus = new BuiltInOverload(SyntaxKind::Plus,this, "nop", Plus);
        plus->PushParameterType(this);
        builtInOverloads[6] = { SyntaxKind::Plus, plus };

        const auto negation = new BuiltInOverload(SyntaxKind::Minus, this, "neg", Minus);
        negation->PushParameterType(this);
        builtInOverloads[7] = { SyntaxKind::Minus, negation };

        const auto increment = new ImplicitOverload(SyntaxKind::Increment, this, "ldc.r8 1 add");
        increment->PushParameterType(this);
        increment->PushParameterType(this);
        overloads[0] = { SyntaxKind::Increment, increment };

        const auto decrement = new ImplicitOverload(SyntaxKind::Decrement, this, "ldc.r8 1 sub");
        decrement->PushParameterType(this);
        decrement->PushParameterType(this);
        overloads[1] = { SyntaxKind::Decrement, decrement };

        const auto greater = new BuiltInOverload(SyntaxKind::GreaterThan, Boolean::Instance(), "cgt", GreaterThan<double>);
        greater->PushParameterType(this);
        greater->PushParameterType(this);
        builtInOverloads[8] = { SyntaxKind::GreaterThan, greater };

        const auto lesser = new BuiltInOverload(SyntaxKind::LesserThan, Boolean::Instance(), "clt", LesserThan<double>);
        lesser->PushParameterType(this);
        lesser->PushParameterType(this);
        builtInOverloads[9] = { SyntaxKind::LesserThan, lesser };

        const auto greaterEquals = new BuiltInOverload(SyntaxKind::GreaterThanEquals, Boolean::Instance(), "clt ldc.i4.0 ceq", GreaterThanEquals<double>);
        greaterEquals->PushParameterType(this);
        greaterEquals->PushParameterType(this);
        builtInOverloads[10] = { SyntaxKind::GreaterThanEquals, greaterEquals };

        const auto lesserEquals = new BuiltInOverload(SyntaxKind::LesserThanEquals, Boolean::Instance(), "cgt ldc.i4.0 ceq", LesserThanEquals<double>);
        lesserEquals->PushParameterType(this);
        lesserEquals->PushParameterType(this);
        builtInOverloads[11] = { SyntaxKind::LesserThanEquals, lesserEquals };
    }

    const ICharacteristic* Double::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    const IFunctionDefinition* Double::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) & ArgumentHash(argumentList);

        for (const auto function: functions)
            if (function.first == hash)
                return function.second;

        return nullptr;
    }

    const IConstructor* Double::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Double::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Double::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Double::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        return FindBuiltInCast(returnType, fromType);
    }

    const IBuiltInCast* Double::FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });

        for (const auto cast: explicitCasts)
            if (cast.first == hash)
                return cast.second;

        return nullptr;
    }

    const IOperatorOverload* Double::FindOverload(const SyntaxKind base) const
    {
        switch (base)
        {
            case SyntaxKind::Increment:
                return overloads[0].second;
            case SyntaxKind::Decrement:
                return overloads[1].second;
            default:
                return FindBuiltInOverload(base);
        }
    }

    const IBuiltInOverload* Double::FindBuiltInOverload(const SyntaxKind base) const
    {
        for (const auto overload: builtInOverloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    Double::~Double()
    {
        for (const auto characteristic : characteristics)
            delete characteristic;

        for (const auto function: functions)
            delete function.second;

        for (const auto cast: explicitCasts)
            delete cast.second;

        for (const auto overload: overloads)
            delete overload.second;

        for (const auto overload: builtInOverloads)
            delete overload.second;
    }
}
