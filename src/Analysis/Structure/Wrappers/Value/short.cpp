#include "short.h"

#include "../../DataTypes/data_type_extensions.h"

#include "integer.h"
#include "long.h"
#include "./float.h"
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

const string cil_short = "[System.Runtime]System.Int16";

namespace
{
    CompilationResult Addition(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Short::Instance(), std::get<short>(arguments[0].data) + std::get<short>(arguments[1].data)} ; }
    CompilationResult Subtraction(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Short::Instance(), std::get<short>(arguments[0].data) - std::get<short>(arguments[1].data)} ; }
    CompilationResult Multiplication(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Short::Instance(), std::get<short>(arguments[0].data) * std::get<short>(arguments[1].data)} ; }
    CompilationResult Division(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Short::Instance(), std::get<short>(arguments[0].data) / std::get<short>(arguments[1].data)} ; }
    CompilationResult Modulus(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Short::Instance(), std::get<short>(arguments[0].data) % std::get<short>(arguments[1].data)} ; }

    CompilationResult Plus(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Short::Instance(), arguments[0].data }; }
    CompilationResult Minus(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Short::Instance(), -std::get<short>(arguments[0].data) }; }

    CompilationResult Not(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Integer::Instance(), ~std::get<short>(arguments[0].data)} ; }
    CompilationResult BitwiseAnd(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Integer::Instance(), std::get<short>(arguments[0].data) & std::get<short>(arguments[1].data)} ; }
    CompilationResult BitwiseOr(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Integer::Instance(), std::get<short>(arguments[0].data) | std::get<short>(arguments[1].data)} ; }
    CompilationResult RightShift(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Integer::Instance(), std::get<short>(arguments[0].data) >> std::get<short>(arguments[1].data)} ; }
    CompilationResult LeftShift(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Integer::Instance(), std::get<short>(arguments[0].data) << std::get<short>(arguments[1].data)} ; }
    CompilationResult BitwiseXor(const std::vector<CompilationResult>& arguments) { return { &Analysis::Structure::Wrappers::Integer::Instance(), std::get<short>(arguments[0].data) ^ std::get<short>(arguments[1].data)} ; }
}

namespace Analysis::Structure::Wrappers
{
    Short::Short() : BuiltInValueType(cil_short, Describer::Public), SingletonService(), characteristics(), tryParse(nullptr), implicitCasts(), explicitCasts(), overloads()
    { }

    const Short& Short::Instance()
    {
        static const Short instance;
        return instance;
    }

    int Short::SlotCount() const { return 1; }

    TypeKind Short::Type() const { return TypeKind::Short; }

    void Short::InitializeMembers()
    {
        characteristics["Max"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "Max", &Instance(), true, "ldc.i2 32767", false, "");
        characteristics["Min"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "Min", &Instance(), true, "ldc.i2 -32767", false, "");

        tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Int16::TryParse(string, int16&)");
        tryParse->PushParameterType(&String::Instance());
        tryParse->PushParameterType(Referenced::Instance(&Instance()));

        const auto implicitInt = new BuiltInCast(&Integer::Instance(), "conv.i4", IntCast<short>);
        implicitInt->PushParameterType(&Instance());
        implicitCasts[ArgumentHash({ &Integer::Instance(), &Instance()})] = implicitInt;
        explicitCasts[ArgumentHash({ &Integer::Instance(), &Instance()})] = implicitInt;

        const auto implicitLong = new BuiltInCast(&Long::Instance(), "conv.i8", LongCast<short>);
        implicitLong->PushParameterType(&Instance());
        implicitCasts[ArgumentHash({ &Long::Instance(), &Instance()})] = implicitLong;
        explicitCasts[ArgumentHash({ &Long::Instance(), &Instance()})] = implicitLong;

        const auto implicitFloat = new BuiltInCast(&Float::Instance(), "conv.r4", FloatCast<short>);
        implicitFloat->PushParameterType(&Instance());
        implicitCasts[ArgumentHash({ &Float::Instance(), &Instance()})] = implicitFloat;
        explicitCasts[ArgumentHash({ &Float::Instance(), &Instance()})] = implicitFloat;

        const auto implicitDouble = new BuiltInCast(&Double::Instance(), "conv.r8", DoubleCast<short>);
        implicitDouble->PushParameterType(&Instance());
        implicitCasts[ArgumentHash({ &Double::Instance(), &Instance()})] = implicitDouble;
        explicitCasts[ArgumentHash({ &Double::Instance(), &Instance()})] = implicitDouble;

        const auto explicitString = new BuiltInCast(&String::Instance(), "call instance string valuetype [System.Runtime]System.Int16::ToString()", StringCast<short>);
        explicitString->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &String::Instance(), &Instance()})] = explicitString;

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, &Boolean::Instance(), "ceq", Equals<short>);
        equals->PushParameterType(&Instance());
        equals->PushParameterType(&Instance());
        overloads[SyntaxKind::Equals] = equals;

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, &Boolean::Instance(), "ceq ldc.i4.0 ceq", NotEquals<short>);
        notEquals->PushParameterType(&Instance());
        notEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::NotEquals] = notEquals;

        const auto addition = new BuiltInOperation(SyntaxKind::Addition, &Instance(), "add conv.i2", Addition);
        addition->PushParameterType(&Instance());
        addition->PushParameterType(&Instance());
        overloads[SyntaxKind::Addition] = addition;

        const auto subtraction = new BuiltInOperation(SyntaxKind::Subtraction, &Instance(), "sub conv.i2", Subtraction);
        subtraction->PushParameterType(&Instance());
        subtraction->PushParameterType(&Instance());
        overloads[SyntaxKind::Subtraction] = subtraction;

        const auto multiplication = new BuiltInOperation(SyntaxKind::Multiplication, &Instance(), "mul conv.i2", Multiplication);
        multiplication->PushParameterType(&Instance());
        multiplication->PushParameterType(&Instance());
        overloads[SyntaxKind::Multiplication] = multiplication;

        const auto division = new BuiltInOperation(SyntaxKind::Division, &Instance(), "div conv.i2", Division);
        division->PushParameterType(&Instance());
        division->PushParameterType(&Instance());
        overloads[SyntaxKind::Division] = division;

        const auto remainder = new BuiltInOperation(SyntaxKind::Modulus, &Instance(), "rem conv.i2", Modulus);
        remainder->PushParameterType(&Instance());
        remainder->PushParameterType(&Instance());
        overloads[SyntaxKind::Modulus] = remainder;

        const auto plus = new BuiltInOperation(SyntaxKind::Plus, &Instance(), "", Plus);
        plus->PushParameterType(&Instance());
        overloads[SyntaxKind::Plus] = plus;

        const auto negation = new BuiltInOperation(SyntaxKind::Minus, &Instance(), "neg", Minus);
        negation->PushParameterType(&Instance());
        overloads[SyntaxKind::Minus] = negation;

        const auto increment = new BuiltInOperation(SyntaxKind::Increment, &Instance(), "ldc.r8 1.0 add conv.i2", nullptr);
        increment->PushParameterType(&Instance());
        increment->PushParameterType(&Instance());
        overloads[SyntaxKind::Increment] = increment;

        const auto decrement = new BuiltInOperation(SyntaxKind::Decrement, &Instance(), "ldc.r8 1.0 sub conv.i2", nullptr);
        decrement->PushParameterType(&Instance());
        decrement->PushParameterType(&Instance());
        overloads[SyntaxKind::Decrement] = decrement;

        const auto greater = new BuiltInOperation(SyntaxKind::GreaterThan, &Boolean::Instance(), "cgt", GreaterThan<short>);
        greater->PushParameterType(&Instance());
        greater->PushParameterType(&Instance());
        overloads[SyntaxKind::GreaterThan] = greater;

        const auto lesser = new BuiltInOperation(SyntaxKind::LesserThan, &Boolean::Instance(), "clt", LesserThan<short>);
        lesser->PushParameterType(&Instance());
        lesser->PushParameterType(&Instance());
        overloads[SyntaxKind::LesserThan] = lesser;

        const auto greaterEquals = new BuiltInOperation(SyntaxKind::GreaterThanEquals, &Boolean::Instance(), "clt ldc.i4.0 ceq", GreaterThanEquals<short>);
        greaterEquals->PushParameterType(&Instance());
        greaterEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::GreaterThanEquals] = greaterEquals;

        const auto lesserEquals = new BuiltInOperation(SyntaxKind::LesserThanEquals, &Boolean::Instance(), "cgt ldc.i4.0 ceq", LesserThanEquals<short>);
        lesserEquals->PushParameterType(&Instance());
        lesserEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::LesserThanEquals] = lesserEquals;

        const auto bitwiseNot = new BuiltInOperation(SyntaxKind::BitwiseNot, &Integer::Instance(), "not", Not);
        bitwiseNot->PushParameterType(&Instance());
        overloads[SyntaxKind::BitwiseNot] = bitwiseNot;

        const auto bitwiseAnd = new BuiltInOperation(SyntaxKind::BitwiseAnd, &Integer::Instance(), "and", BitwiseAnd);
        bitwiseAnd->PushParameterType(&Instance());
        bitwiseAnd->PushParameterType(&Instance());
        overloads[SyntaxKind::BitwiseAnd] = bitwiseAnd;

        const auto bitwiseOr = new BuiltInOperation(SyntaxKind::BitwiseOr, &Integer::Instance(), "or", BitwiseOr);
        bitwiseOr->PushParameterType(&Instance());
        bitwiseOr->PushParameterType(&Instance());
        overloads[SyntaxKind::BitwiseOr] = bitwiseOr;

        const auto bitwiseXor = new BuiltInOperation(SyntaxKind::BitwiseXor, &Integer::Instance(), "xor", BitwiseXor);
        bitwiseXor->PushParameterType(&Instance());
        bitwiseXor->PushParameterType(&Instance());
        overloads[SyntaxKind::BitwiseXor] = bitwiseXor;

        const auto rightShift = new BuiltInOperation(SyntaxKind::RightShift, &Integer::Instance(), "shr", RightShift);
        rightShift->PushParameterType(&Instance());
        rightShift->PushParameterType(&Instance());
        overloads[SyntaxKind::RightShift] = rightShift;

        const auto leftShift = new BuiltInOperation(SyntaxKind::LeftShift, &Integer::Instance(), "shl", LeftShift);
        leftShift->PushParameterType(&Instance());
        leftShift->PushParameterType(&Instance());
        overloads[SyntaxKind::LeftShift] = leftShift;
    }

    const ICharacteristic* Short::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? nullptr : characteristics.at(name);
    }

    const IFunctionDefinition* Short::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        if (name != "TryParse" || ArgumentHash(argumentList) != ArgumentHash(tryParse))
            return nullptr;

        return tryParse;
    }

    const IFunction* Short::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Short::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Short::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });
        return implicitCasts.contains(hash) ? nullptr : implicitCasts.at(hash);
    }

    const IFunction* Short::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        return FindBuiltInCast(returnType, fromType);
    }

    const IBuiltInCast* Short::FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });
        return explicitCasts.contains(hash) ? nullptr : explicitCasts.at(hash);
    }

    const IOperatorOverload* Short::FindOverload(const SyntaxKind base) const
    {
        return overloads.contains(base) ? nullptr : overloads.at(base);
    }

    const IBuiltInOverload* Short::FindBuiltInOverload(const SyntaxKind base) const
    {
        return overloads.contains(base) ? nullptr : overloads.at(base);
    }

    Short::~Short()
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
