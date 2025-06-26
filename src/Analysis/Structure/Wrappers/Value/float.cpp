#include "./float.h"

#include "short.h"
#include "integer.h"
#include "long.h"
#include "double.h"
#include "boolean.h"
#include "built_in_functions.h"

#include "../Reference/string.h"
#include "../Generic/referenced.h"

#include "../../DataTypes/data_type_extensions.h"

#include "../../Compilation/compilation_result.h"

#include "../../Context/Constants/float_constant.h"

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
    CompilationResult Addition(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Float::Instance(), std::get<float>(arguments[0].data) + std::get<float>(arguments[1].data)} ; }
    CompilationResult Subtraction(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Float::Instance(), std::get<float>(arguments[0].data) - std::get<float>(arguments[1].data)} ; }
    CompilationResult Multiplication(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Float::Instance(), std::get<float>(arguments[0].data) * std::get<float>(arguments[1].data)} ; }
    CompilationResult Division(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Float::Instance(), std::get<float>(arguments[0].data) / std::get<float>(arguments[1].data)} ; }

    CompilationResult Plus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Float::Instance(), arguments[0].data }; }
    CompilationResult Minus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Float::Instance(), -std::get<float>(arguments[0].data) }; }
}

namespace Analysis::Structure::Wrappers
{
    Float::Float() : BuiltInValueType("float32", Describer::Public), SingletonService(), characteristics(), implicitDouble(nullptr)
    { }

    Float Float::instance;

    const Float* Float::Instance() { return &instance; }

    void Float::BindGlobalInstance()
    {
        static bool bound;

        if (!bound)
        {
            instance.BindGlobal();
            bound = true;
        }
    }

    int Float::SlotCount() const { return 1; }

    TypeKind Float::Type() const { return TypeKind::Float; }

    void Float::BindGlobal()
    {
        characteristics[0] = new BuiltInConstant("Max", Describer::Public | Describer::Constexpr, this, new FloatConstant(3.4028235E+38));
        characteristics[1] = new BuiltInConstant("Min", Describer::Public | Describer::Constexpr, this, new FloatConstant(-3.4028235E+38));

        characteristics[2] = new BuiltInProperty("NaN", Describer::PublicStatic | Describer::Const, this, true, "ldc.r4 NaN", false, "");
        characteristics[3] = new BuiltInProperty("PositiveInfinity", Describer::PublicStatic | Describer::Const, this, true, "ldc.r4 Infinity", false, "");
        characteristics[4] = new BuiltInProperty("NegativeInfinity", Describer::PublicStatic | Describer::Const, this, true, "ldc.r4 -Infinity", false, "");

        characteristics[5] = new BuiltInConstant("Epsilon", Describer::Public | Describer::Constexpr, this, new FloatConstant(1.401298E-45));

        const auto tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, Boolean::Instance(), "call bool [System.Runtime]System.Single::TryParse(string, float32&)");
        tryParse->PushParameterType(String::Instance());
        tryParse->PushParameterType(Referenced::Instance(this));
        functions[0] = { std::hash<string>()(tryParse->Name()) ^ ArgumentHash(tryParse), tryParse };

        const auto getHash = GetHash();
        functions[1] = { std::hash<string>()(getHash->Name()) ^ ArgumentHash(getHash), getHash };

        const auto explicitShort = new BuiltInCast(Short::Instance(), "conv.i2", ShortCast<float>);
        explicitShort->PushParameterType(this);
        explicitCasts[0] = { ArgumentHash({ Short::Instance(), this }), explicitShort };

        const auto explicitInteger = new BuiltInCast(Integer::Instance(), "conv.i4", IntCast<float>);
        explicitInteger->PushParameterType(this);
        explicitCasts[1] = { ArgumentHash({ Integer::Instance(), this }), explicitInteger };

        const auto explicitLong = new BuiltInCast(Long::Instance(), "conv.i8", LongCast<float>);
        explicitLong->PushParameterType(this);
        explicitCasts[2] = { ArgumentHash({ Long::Instance(), this }), explicitLong };

        const auto implicitDouble = new BuiltInCast(Double::Instance(), "conv.r8", DoubleCast<float>);
        implicitDouble->PushParameterType(this);
        this->implicitDouble = implicitDouble;
        explicitCasts[3] = { ArgumentHash({ Double::Instance(), this }), new BuiltInCast(*implicitDouble) };

        const auto explicitString = new BuiltInCast(String::Instance(), "call instance string [System.Runtime]System.Single::ToString()", StringCast<float>);
        explicitString->PushParameterType(this);
        explicitCasts[4] = { ArgumentHash({ String::Instance(), this }), explicitString };

        const auto equals = new BuiltInOverload(SyntaxKind::Equals, Boolean::Instance(), "ceq", Equals<float>);
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        builtInOverloads[0] = { SyntaxKind::Equals, equals };

        const auto notEquals = new BuiltInOverload(SyntaxKind::NotEquals, Boolean::Instance(), "ceq ldc.i4.0 ceq", NotEquals<float>);
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

        const auto increment = new GeneratedOverload(SyntaxKind::Increment, this, "ldc.r4 1 add");
        increment->PushParameterType(this);
        increment->PushParameterType(this);
        overloads[0] = { SyntaxKind::Increment, increment };

        const auto decrement = new GeneratedOverload(SyntaxKind::Decrement, this, "ldc.r4 1 sub");
        decrement->PushParameterType(this);
        decrement->PushParameterType(this);
        overloads[1] = { SyntaxKind::Decrement, decrement };

        const auto greater = new BuiltInOverload(SyntaxKind::GreaterThan, Boolean::Instance(), "cgt", GreaterThan<float>);
        greater->PushParameterType(this);
        greater->PushParameterType(this);
        builtInOverloads[8] = { SyntaxKind::GreaterThan, greater };

        const auto lesser = new BuiltInOverload(SyntaxKind::LesserThan, Boolean::Instance(), "clt", LesserThan<float>);
        lesser->PushParameterType(this);
        lesser->PushParameterType(this);
        builtInOverloads[9] = { SyntaxKind::LesserThan, lesser };

        const auto greaterEquals = new BuiltInOverload(SyntaxKind::GreaterThanEquals, Boolean::Instance(), "clt ldc.i4.0 ceq", GreaterThanEquals<float>);
        greaterEquals->PushParameterType(this);
        greaterEquals->PushParameterType(this);
        builtInOverloads[10] = { SyntaxKind::GreaterThanEquals, greaterEquals };

        const auto lesserEquals = new BuiltInOverload(SyntaxKind::LesserThanEquals, Boolean::Instance(), "cgt ldc.i4.0 ceq", LesserThanEquals<float>);
        lesserEquals->PushParameterType(this);
        lesserEquals->PushParameterType(this);
        builtInOverloads[11] = { SyntaxKind::LesserThanEquals, lesserEquals };
    }

    const ICharacteristic* Float::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    const IFunctionDefinition* Float::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) & ArgumentHash(argumentList);

        for (const auto function: functions)
            if (function.first == hash)
                return function.second;

        return nullptr;
    }

    const IConstructor* Float::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Float::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Float::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        if (returnType == Double::Instance() && fromType == this)
            return implicitDouble;

        return nullptr;
    }

    const IFunction* Float::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        return FindBuiltInCast(returnType, fromType);
    }

    const IBuiltInCast* Float::FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });

        for (const auto cast: explicitCasts)
            if (cast.first == hash)
                return cast.second;

        return nullptr;
    }

    const IOperatorOverload* Float::FindOverload(const SyntaxKind base) const
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

    const IBuiltInOverload* Float::FindBuiltInOverload(const SyntaxKind base) const
    {
        for (const auto overload: builtInOverloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    Float::~Float()
    {
        for (const auto characteristic : characteristics)
            delete characteristic;

        for (const auto function: functions)
            delete function.second;

        delete implicitDouble;

        for (const auto cast: explicitCasts)
            delete cast.second;

        for (const auto overload: overloads)
            delete overload.second;

        for (const auto overload: builtInOverloads)
            delete overload.second;
    }
}

