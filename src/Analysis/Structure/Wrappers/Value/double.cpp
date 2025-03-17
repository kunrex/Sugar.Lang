#include "double.h"

#include "../../DataTypes/data_type_extensions.h"

#include "short.h"
#include "integer.h"
#include "long.h"
#include "./float.h"
#include "boolean.h"
#include "../Reference/string.h"
#include "../Generic/referenced.h"

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_operation.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

constexpr std::string cil_double = "[System.Runtime]System.Double";

namespace Analysis::Structure::Wrappers
{
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

        const auto explicitShort = new BuiltInCast(&Short::Instance(), "conv.i2");
        explicitShort->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Short::Instance(), &Instance() })] = explicitShort;

        const auto explicitInteger = new BuiltInCast(&Integer::Instance(), "conv.i4");
        explicitInteger->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Integer::Instance(), &Instance() })] = explicitInteger;

        const auto explicitLong = new BuiltInCast(&Long::Instance(), "conv.i8");
        explicitLong->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Long::Instance(), &Instance() })] = explicitLong;

        const auto explicitFloat = new BuiltInCast(&Float::Instance(), "conv.r4");
        explicitFloat->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Float::Instance(), &Instance() })] = explicitFloat;

        const auto explicitString = new BuiltInCast(&String::Instance(), "call instance string valuetype [System.Runtime]System.Double::ToString()");
        explicitString->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &String::Instance(), &Instance() })] = explicitShort;

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, &Boolean::Instance(), "ceq");
        equals->PushParameterType(&Instance());
        equals->PushParameterType(&Instance());
        overloads[SyntaxKind::Equals] = equals;

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, &Boolean::Instance(), "ceq ldc.i4.0 ceq");
        notEquals->PushParameterType(&Instance());
        notEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::NotEquals] = notEquals;

        const auto addition = new BuiltInOperation(SyntaxKind::Addition, &Instance(), "add");
        addition->PushParameterType(&Instance());
        addition->PushParameterType(&Instance());
        overloads[SyntaxKind::Addition] = addition;

        const auto subtraction = new BuiltInOperation(SyntaxKind::Subtraction, &Instance(), "sub");
        subtraction->PushParameterType(&Instance());
        subtraction->PushParameterType(&Instance());
        overloads[SyntaxKind::Subtraction] = subtraction;

        const auto multiplication = new BuiltInOperation(SyntaxKind::Multiplication, &Instance(), "mul");
        multiplication->PushParameterType(&Instance());
        multiplication->PushParameterType(&Instance());
        overloads[SyntaxKind::Multiplication] = multiplication;

        const auto division = new BuiltInOperation(SyntaxKind::Division, &Instance(), "div");
        division->PushParameterType(&Instance());
        division->PushParameterType(&Instance());
        overloads[SyntaxKind::Division] = division;

        const auto remainder = new BuiltInOperation(SyntaxKind::Modulus, &Instance(), "rem");
        remainder->PushParameterType(&Instance());
        remainder->PushParameterType(&Instance());
        overloads[SyntaxKind::Modulus] = remainder;

        const auto plus = new BuiltInOperation(SyntaxKind::Plus, &Instance(), "");
        plus->PushParameterType(&Instance());
        overloads[SyntaxKind::Plus] = plus;

        const auto negation = new BuiltInOperation(SyntaxKind::Minus, &Instance(), "neg");
        negation->PushParameterType(&Instance());
        overloads[SyntaxKind::Minus] = negation;

        const auto increment = new BuiltInOperation(SyntaxKind::Increment, &Instance(), "ldc.r8 1.0 add");
        increment->PushParameterType(&Instance());
        increment->PushParameterType(&Instance());
        overloads[SyntaxKind::Increment] = increment;
        overloads[SyntaxKind::IncrementPrefix] = increment;

        const auto decrement = new BuiltInOperation(SyntaxKind::Decrement, &Instance(), "ldc.r8 1.0 sub");
        decrement->PushParameterType(&Instance());
        decrement->PushParameterType(&Instance());
        overloads[SyntaxKind::Decrement] = decrement;
        overloads[SyntaxKind::DecrementPrefix] = decrement;

        const auto greater = new BuiltInOperation(SyntaxKind::GreaterThan, &Boolean::Instance(), "cgt");
        greater->PushParameterType(&Instance());
        greater->PushParameterType(&Instance());
        overloads[SyntaxKind::GreaterThan] = greater;

        const auto lesser = new BuiltInOperation(SyntaxKind::LesserThan, &Boolean::Instance(), "clt");
        lesser->PushParameterType(&Instance());
        lesser->PushParameterType(&Instance());
        overloads[SyntaxKind::LesserThan] = lesser;

        const auto greaterEquals = new BuiltInOperation(SyntaxKind::GreaterThanEquals, &Boolean::Instance(), "clt ldc.i4.0 ceq");
        greaterEquals->PushParameterType(&Instance());
        greaterEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::GreaterThanEquals] = greaterEquals;

        const auto lesserEquals = new BuiltInOperation(SyntaxKind::LesserThanEquals, &Boolean::Instance(), "cgt ldc.i4.0 ceq");
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
        const auto hash = ArgumentHash({ returnType , fromType });
        return explicitCasts.contains(hash) ? nullptr : explicitCasts.at(hash);
    }

    const IOperatorOverload* Double::FindOverload(const SyntaxKind base) const
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
