#include "./float.h"

#include "../../DataTypes/data_type_extensions.h"

#include "short.h"
#include "integer.h"
#include "long.h"
#include "double.h"
#include "boolean.h"
#include "built_in_functions.h"
#include "../Reference/string.h"
#include "../Generic/referenced.h"

#include "../../Compilation/compilation_result.h"

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_operation.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_float = "[System.Runtime]System.Single";

namespace
{
    CompilationResult Addition(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Float::Instance(), std::get<float>(arguments[0].data) + std::get<float>(arguments[1].data)} ; }
    CompilationResult Subtraction(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Float::Instance(), std::get<float>(arguments[0].data) - std::get<float>(arguments[1].data)} ; }
    CompilationResult Multiplication(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Float::Instance(), std::get<float>(arguments[0].data) * std::get<float>(arguments[1].data)} ; }
    CompilationResult Division(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Float::Instance(), std::get<float>(arguments[0].data) / std::get<float>(arguments[1].data)} ; }

    CompilationResult Plus(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Float::Instance(), arguments[0].data }; }
    CompilationResult Minus(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Float::Instance(), -std::get<float>(arguments[0].data) }; }
}

namespace Analysis::Structure::Wrappers
{

    Float::Float() : BuiltInValueType(cil_float, Describer::Public), SingletonService(), characteristics(), tryParse(nullptr), implicitCasts(), explicitCasts(), overloads()
    { }

    const Float& Float::Instance()
    {
        static const Float instance;
        return instance;
    }


    int Float::SlotCount() const { return 1; }

    TypeKind Float::Type() const { return TypeKind::Float; }

    void Float::BindGlobal()
    {
        characteristics["Max"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "Max", &Instance(), true, "ldc.r4 3.4028235E+38", false, "");
        characteristics["Min"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "Min", &Instance(), true, "ldc.r4 -3.4028235E+38", false, "");

        characteristics["NaN"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "NaN", &Instance(), true, "ldc.r4 NaN", false, "");
        characteristics["PositiveInfinity"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "PositiveInfinity", &Instance(), true, "ldc.r4 Infinity", false, "");
        characteristics["NegativeInfinity"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "NegativeInfinity", &Instance(), true, "ldc.r4 -Infinity", false, "");

        characteristics["Epsilon"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "Epsilon", &Instance(), true, "ldc.r4 1.401298E-45", false, "");

        tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Single::TryParse(string, float32&)");
        tryParse->PushParameterType(&String::Instance());
        tryParse->PushParameterType(Referenced::Instance(&Instance()));

        const auto explicitShort = new BuiltInCast(&Short::Instance(), "conv.i2", ShortCast<float>);
        explicitShort->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Short::Instance(), &Instance() })] = explicitShort;

        const auto explicitInteger = new BuiltInCast(&Integer::Instance(), "conv.i4", IntCast<float>);
        explicitInteger->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Integer::Instance(), &Instance() })] = explicitInteger;

        const auto explicitLong = new BuiltInCast(&Long::Instance(), "conv.i8", LongCast<float>);
        explicitLong->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Long::Instance(), &Instance() })] = explicitLong;

        const auto implicitDouble = new BuiltInCast(&Double::Instance(), "conv.r8", DoubleCast<float>);
        implicitDouble->PushParameterType(&Instance());
        implicitCasts[ArgumentHash({ &Double::Instance(), &Instance() })] = implicitDouble;
        explicitCasts[ArgumentHash({ &Double::Instance(), &Instance() })] = implicitDouble;

        const auto explicitString = new BuiltInCast(&String::Instance(), "call instance string valuetype [System.Runtime]System.Single::ToString()", StringCast<float>);
        explicitString->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &String::Instance(), &Instance() })] = explicitString;

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, &Boolean::Instance(), "ceq", Equals<double>);
        equals->PushParameterType(&Instance());
        equals->PushParameterType(&Instance());
        overloads[SyntaxKind::Equals] = equals;

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, &Boolean::Instance(), "ceq ldc.i4.0 ceq", NotEquals<double>);
        notEquals->PushParameterType(&Instance());
        notEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::NotEquals] = notEquals;

        const auto addition = new BuiltInOperation(SyntaxKind::Addition, &Instance(), "add", Addition);
        addition->PushParameterType(&Instance());
        addition->PushParameterType(&Instance());
        overloads[SyntaxKind::Addition] = addition;

        const auto subtraction = new BuiltInOperation(SyntaxKind::Subtraction, &Instance(), "sub", Subtraction);
        subtraction->PushParameterType(&Instance());
        subtraction->PushParameterType(&Instance());
        overloads[SyntaxKind::Subtraction] = subtraction;

        const auto multiplication = new BuiltInOperation(SyntaxKind::Multiplication, &Instance(), "mul", Multiplication);
        multiplication->PushParameterType(&Instance());
        multiplication->PushParameterType(&Instance());
        overloads[SyntaxKind::Multiplication] = multiplication;

        const auto division = new BuiltInOperation(SyntaxKind::Division, &Instance(), "div", Division);
        division->PushParameterType(&Instance());
        division->PushParameterType(&Instance());
        overloads[SyntaxKind::Division] = division;

        const auto plus = new BuiltInOperation(SyntaxKind::Plus, &Instance(), "", Plus);
        plus->PushParameterType(&Instance());
        overloads[SyntaxKind::Plus] = plus;

        const auto negation = new BuiltInOperation(SyntaxKind::Minus, &Instance(), "neg", Minus);
        negation->PushParameterType(&Instance());
        overloads[SyntaxKind::Minus] = negation;

        const auto increment = new BuiltInOperation(SyntaxKind::Increment, &Instance(), "ldc.r8 1.0 add", nullptr);
        increment->PushParameterType(&Instance());
        increment->PushParameterType(&Instance());
        overloads[SyntaxKind::Increment] = increment;

        const auto decrement = new BuiltInOperation(SyntaxKind::Decrement, &Instance(), "ldc.r8 1.0 sub", nullptr);
        decrement->PushParameterType(&Instance());
        decrement->PushParameterType(&Instance());
        overloads[SyntaxKind::Decrement] = decrement;

        const auto greater = new BuiltInOperation(SyntaxKind::GreaterThan, &Boolean::Instance(), "cgt", GreaterThan<float>);
        greater->PushParameterType(&Instance());
        greater->PushParameterType(&Instance());
        overloads[SyntaxKind::GreaterThan] = greater;

        const auto lesser = new BuiltInOperation(SyntaxKind::LesserThan, &Boolean::Instance(), "clt", LesserThan<float>);
        lesser->PushParameterType(&Instance());
        lesser->PushParameterType(&Instance());
        overloads[SyntaxKind::LesserThan] = lesser;

        const auto greaterEquals = new BuiltInOperation(SyntaxKind::GreaterThanEquals, &Boolean::Instance(), "clt ldc.i4.0 ceq", GreaterThanEquals<float>);
        greaterEquals->PushParameterType(&Instance());
        greaterEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::GreaterThanEquals] = greaterEquals;

        const auto lesserEquals = new BuiltInOperation(SyntaxKind::LesserThanEquals, &Boolean::Instance(), "cgt ldc.i4.0 ceq", LesserThanEquals<float>);
        lesserEquals->PushParameterType(&Instance());
        lesserEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::LesserThanEquals] = lesserEquals;
    }

    const ICharacteristic* Float::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? characteristics.at(name) : nullptr;
    }

    const IFunctionDefinition* Float::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        if (name != "TryParse" || ArgumentHash(argumentList) != ArgumentHash(tryParse))
            return nullptr;

        return tryParse;
    }

    const IFunction* Float::FindConstructor(const bool isStatic, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Float::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Float::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });
        return implicitCasts.contains(hash) ? implicitCasts.at(hash) : nullptr;
    }

    const IFunction* Float::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        return FindBuiltInCast(returnType, fromType);
    }

    const IBuiltInCast* Float::FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });
        return explicitCasts.contains(hash) ? explicitCasts.at(hash) : nullptr;
    }

    const IOperatorOverload* Float::FindOverload(const SyntaxKind base) const
    {
        return overloads.contains(base) ? overloads.at(base) : nullptr;
    }

    const IBuiltInOverload* Float::FindBuiltInOverload(const SyntaxKind base) const
    {
        return overloads.contains(base) ? overloads.at(base) : nullptr;
    }

    Float::~Float()
    {
        delete tryParse;

        for (const auto cast: implicitCasts)
            delete cast.second;

        for (const auto cast: explicitCasts)
            delete cast.second;

        for (const auto overload: overloads)
            delete overload.second;
    }
}

