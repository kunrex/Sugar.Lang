#include "double.h"

#include "../../DataTypes/data_type_extensions.h"

#include "short.h"
#include "integer.h"
#include "long.h"
#include "./float.h"
#include "boolean.h"
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

constexpr std::string cil_double = "[System.Runtime]System.Double";

namespace Analysis::Structure::Wrappers
{
    CompilationResult ExplicitShort(const CompilationResult& argument) { return  { &Short::Instance(), static_cast<long>(std::get<double>(argument.data)) }; }
    CompilationResult ExplicitInteger(const CompilationResult& argument) { return  { &Integer::Instance(), static_cast<long>(std::get<double>(argument.data)) }; }
    CompilationResult ExplicitLong(const CompilationResult& argument) { return  { &Long::Instance(), static_cast<long>(std::get<double>(argument.data)) }; }

    CompilationResult ExplicitFloat(const CompilationResult& argument) { return  { &Float::Instance(), std::get<double>(argument.data) }; }

    CompilationResult ExplicitString(const CompilationResult& argument) { return  { &String::Instance(), std::to_string(std::get<double>(argument.data)) }; }

    CompilationResult Equals(const std::vector<CompilationResult>& arguments) { return { &Boolean::Instance(), static_cast<long>(arguments[0].data == arguments[1].data)} ; }
    CompilationResult NotEquals(const std::vector<CompilationResult>& arguments) { return { &Boolean::Instance(), static_cast<long>(arguments[0].data != arguments[1].data)} ; }

    CompilationResult Addition(const std::vector<CompilationResult>& arguments) { return { &Double::Instance(), std::get<double>(arguments[0].data) + std::get<double>(arguments[1].data)} ; }
    CompilationResult Subtraction(const std::vector<CompilationResult>& arguments) { return { &Double::Instance(), std::get<double>(arguments[0].data) - std::get<double>(arguments[1].data)} ; }
    CompilationResult Multiplication(const std::vector<CompilationResult>& arguments) { return { &Double::Instance(), std::get<double>(arguments[0].data) * std::get<double>(arguments[1].data)} ; }
    CompilationResult Division(const std::vector<CompilationResult>& arguments) { return { &Double::Instance(), std::get<double>(arguments[0].data) / std::get<double>(arguments[1].data)} ; }

    CompilationResult Plus(const std::vector<CompilationResult>& arguments) { return { &Double::Instance(), arguments[0].data }; }
    CompilationResult Minus(const std::vector<CompilationResult>& arguments) { return { &Double::Instance(), -std::get<double>(arguments[0].data) }; }

    CompilationResult GreaterThan(const std::vector<CompilationResult>& arguments) { return { &Boolean::Instance(), static_cast<long>(std::get<double>(arguments[0].data) > std::get<double>(arguments[1].data))} ; }
    CompilationResult LesserThan(const std::vector<CompilationResult>& arguments) { return { &Boolean::Instance(), static_cast<long>(std::get<double>(arguments[0].data) < std::get<double>(arguments[1].data))} ; }
    CompilationResult GreaterThanEquals(const std::vector<CompilationResult>& arguments) { return { &Boolean::Instance(), static_cast<long>(std::get<double>(arguments[0].data) >= std::get<double>(arguments[1].data))} ; }
    CompilationResult LesserThanEquals(const std::vector<CompilationResult>& arguments) { return { &Boolean::Instance(), static_cast<long>(std::get<double>(arguments[0].data) <= std::get<double>(arguments[1].data))} ; }

    Double::Double() : BuiltInValueType(cil_double, Describer::Public), SingletonService(), characteristics(), tryParse(nullptr), explicitCasts(), overloads()
    { }

    int Double::SlotCount() const { return 2; }

    TypeKind Double::Type() const { return TypeKind::Double; }

    void Double::InitializeMembers()
    {
        characteristics["Max"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "Max", &Instance(), true, "ldc.r8 1.7976931348623157E+308", false, "");
        characteristics["Min"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "Min", &Instance(), true, "ldc.r8 -1.7976931348623157E+308", false, "");

        characteristics["NaN"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "NaN", &Instance(), true, "ldc.r8 NaN", false, "");
        characteristics["PositiveInfinity"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "PositiveInfinity", &Instance(), true, "ldc.r8 Infinity", false, "");
        characteristics["NegativeInfinity"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "NegativeInfinity", &Instance(), true, "ldc.r8 -Infinity", false, "");

        characteristics["Epsilon"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "Epsilon", &Instance(), true, "ldc.r8 4.94065645841247E-324", false, "");

        tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Double::TryParse(string, float64&)");
        tryParse->PushParameterType(&String::Instance());
        tryParse->PushParameterType(Referenced::Instance(&Instance()));

        const auto explicitShort = new BuiltInCast(&Short::Instance(), "conv.i2", ExplicitShort);
        explicitShort->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Short::Instance(), &Instance() })] = explicitShort;

        const auto explicitInteger = new BuiltInCast(&Integer::Instance(), "conv.i4", ExplicitInteger);
        explicitInteger->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Integer::Instance(), &Instance() })] = explicitInteger;

        const auto explicitLong = new BuiltInCast(&Long::Instance(), "conv.i8", ExplicitLong);
        explicitLong->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Long::Instance(), &Instance() })] = explicitLong;

        const auto explicitFloat = new BuiltInCast(&Float::Instance(), "conv.r4", ExplicitFloat);
        explicitFloat->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Float::Instance(), &Instance() })] = explicitFloat;

        const auto explicitString = new BuiltInCast(&String::Instance(), "call instance string valuetype [System.Runtime]System.Double::ToString()", ExplicitString);
        explicitString->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &String::Instance(), &Instance() })] = explicitShort;

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, &Boolean::Instance(), "ceq", Equals);
        equals->PushParameterType(&Instance());
        equals->PushParameterType(&Instance());
        overloads[SyntaxKind::Equals] = equals;

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, &Boolean::Instance(), "ceq ldc.i4.0 ceq", NotEquals);
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

        const auto greater = new BuiltInOperation(SyntaxKind::GreaterThan, &Boolean::Instance(), "cgt", GreaterThan);
        greater->PushParameterType(&Instance());
        greater->PushParameterType(&Instance());
        overloads[SyntaxKind::GreaterThan] = greater;

        const auto lesser = new BuiltInOperation(SyntaxKind::LesserThan, &Boolean::Instance(), "clt", LesserThan);
        lesser->PushParameterType(&Instance());
        lesser->PushParameterType(&Instance());
        overloads[SyntaxKind::LesserThan] = lesser;

        const auto greaterEquals = new BuiltInOperation(SyntaxKind::GreaterThanEquals, &Boolean::Instance(), "clt ldc.i4.0 ceq", GreaterThanEquals);
        greaterEquals->PushParameterType(&Instance());
        greaterEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::GreaterThanEquals] = greaterEquals;

        const auto lesserEquals = new BuiltInOperation(SyntaxKind::LesserThanEquals, &Boolean::Instance(), "cgt ldc.i4.0 ceq", LesserThan);
        lesserEquals->PushParameterType(&Instance());
        lesserEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::LesserThanEquals] = lesserEquals;
    }

    const ICharacteristic* Double::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? nullptr : characteristics.at(name);
    }

    const IFunctionDefinition* Double::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        if (name != "TryParse" || ArgumentHash(argumentList) != ArgumentHash(tryParse))
            return nullptr;

        return tryParse;
    }

    const IFunction* Double::FindConstructor(const std::vector<const IDataType*>& argumentList) const
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
        return explicitCasts.contains(hash) ? nullptr : explicitCasts.at(hash);
    }

    const IOperatorOverload* Double::FindOverload(const SyntaxKind base) const
    {
        return overloads.contains(base) ? nullptr : overloads.at(base);
    }

    const IBuiltInOverload* Double::FindBuiltInOverload(const SyntaxKind base) const
    {
        return overloads.contains(base) ? nullptr : overloads.at(base);
    }

    Double::~Double()
    {
        for (const auto& characteristic: characteristics)
            delete characteristic.second;

        delete tryParse;

        for (const auto cast: explicitCasts)
            delete cast.second;

        for (const auto overload: overloads)
            delete overload.second;
    }
}
