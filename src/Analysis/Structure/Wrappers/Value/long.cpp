#include "long.h"

#include "../../DataTypes/data_type_extensions.h"

#include "short.h"
#include "integer.h"
#include "./float.h"
#include "double.h"
#include "boolean.h"
#include "built_in_functions.h"
#include "../Reference/string.h"
#include "../Generic/referenced.h"

#include "../../Compilation/compilation_result.h"
#include "../../Context/Constants/integer_constant.h"

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_constant.h"
#include "../../Global/BuiltIn/built_in_operation.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_long = "[System.Runtime]System.Int64";

namespace
{
    CompilationResult Addition(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), std::get<long>(arguments[0].data) + std::get<long>(arguments[1].data)} ; }
    CompilationResult Subtraction(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), std::get<long>(arguments[0].data) - std::get<long>(arguments[1].data)} ; }
    CompilationResult Multiplication(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), std::get<long>(arguments[0].data) * std::get<long>(arguments[1].data)} ; }
    CompilationResult Division(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), std::get<long>(arguments[0].data) / std::get<long>(arguments[1].data)} ; }
    CompilationResult Modulus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), std::get<long>(arguments[0].data) % std::get<long>(arguments[1].data)} ; }

    CompilationResult Plus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), arguments[0].data }; }
    CompilationResult Minus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), -std::get<long>(arguments[0].data) }; }

    CompilationResult Not(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), static_cast<long>(!std::get<long>(arguments[0].data))} ; }
    CompilationResult BitwiseAnd(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), std::get<long>(arguments[0].data) & std::get<long>(arguments[1].data)} ; }
    CompilationResult BitwiseOr(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), std::get<long>(arguments[0].data) | std::get<long>(arguments[1].data)} ; }
    CompilationResult RightShift(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), std::get<long>(arguments[0].data) >> std::get<long>(arguments[1].data)} ; }
    CompilationResult LeftShift(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), std::get<long>(arguments[0].data) << std::get<long>(arguments[1].data)} ; }
    CompilationResult BitwiseXor(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Long::Instance(), std::get<long>(arguments[0].data) ^ std::get<long>(arguments[1].data)} ; }
}

namespace Analysis::Structure::Wrappers
{
    Long::Long() : BuiltInValueType(cil_long, Describer::Public), SingletonService(), tryParse(nullptr), explicitCasts(), overloads()
    { }

    const Long* Long::Instance()
    {
        static const Long instance;
        return &instance;
    }


    int Long::SlotCount() const { return 2; }

    TypeKind Long::Type() const { return TypeKind::Long; }

    void Long::BindGlobal()
    {
        characteristics.push_back(new BuiltInConstant("Max", Describer::Public | Describer::Constexpr, this, new LongConstant(9223372036854775807)));
        characteristics.push_back(new BuiltInConstant("Min", Describer::Public | Describer::Constexpr, this, new LongConstant(-9223372036854775807)));

        tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, Boolean::Instance(), "bool valuetype [System.Runtime]System.Int64::TryParse(string, int64&)");
        tryParse->PushParameterType(String::Instance());
        tryParse->PushParameterType(Referenced::Instance(this));

        const auto explicitShort = new BuiltInCast(Short::Instance(), "conv.i2", ShortCast<long>);
        explicitShort->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ Short::Instance(), this }), explicitShort);

        const auto explicitInt = new BuiltInCast(Integer::Instance(), "conv.i4", IntCast<long>);
        explicitInt->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ Integer::Instance(), this }), explicitInt);

        const auto explicitFloat = new BuiltInCast(Float::Instance(), "conv.r4", FloatCast<long>);
        explicitFloat->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ Float::Instance(), this }), explicitFloat);

        const auto explicitDouble = new BuiltInCast(Double::Instance(), "conv.r8", DoubleCast<long>);
        explicitDouble->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ Double::Instance(), this }), explicitDouble);

        const auto explicitString = new BuiltInCast(String::Instance(), "call instance string valuetype [System.Runtime]System.Int64::ToString()", StringCast<long>);
        explicitString->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ String::Instance(), this }), explicitString);

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, Boolean::Instance(), "ceq", Equals<long>);
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Equals, equals);

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, Boolean::Instance(), "ceq ldc.i4.0 ceq", NotEquals<long>);
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::NotEquals, notEquals);

        const auto addition = new BuiltInOperation(SyntaxKind::Addition, this, "add", Addition);
        addition->PushParameterType(this);
        addition->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Addition, addition);

        const auto subtraction = new BuiltInOperation(SyntaxKind::Subtraction, this, "sub", Subtraction);
        subtraction->PushParameterType(this);
        subtraction->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Subtraction, subtraction);

        const auto multiplication = new BuiltInOperation(SyntaxKind::Multiplication, this, "mul", Multiplication);
        multiplication->PushParameterType(this);
        multiplication->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Multiplication, multiplication);

        const auto division = new BuiltInOperation(SyntaxKind::Division, this, "div", Division);
        division->PushParameterType(this);
        division->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Division, division);

        const auto remainder = new BuiltInOperation(SyntaxKind::Modulus, this, "rem", Modulus);
        remainder->PushParameterType(this);
        remainder->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Modulus, remainder);

        const auto plus = new BuiltInOperation(SyntaxKind::Plus, this, "", Plus);
        plus->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Plus, plus);

        const auto negation = new BuiltInOperation(SyntaxKind::Minus, this, "neg", Minus);
        negation->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Minus, negation);

        const auto increment = new BuiltInOperation(SyntaxKind::Increment, this, "ldc.r8 1.0 add", nullptr);
        increment->PushParameterType(this);
        increment->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Increment, increment);

        const auto decrement = new BuiltInOperation(SyntaxKind::Decrement, this, "ldc.r8 1.0 sub", nullptr);
        decrement->PushParameterType(this);
        decrement->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Decrement, decrement);

        const auto greater = new BuiltInOperation(SyntaxKind::GreaterThan, Boolean::Instance(), "cgt", GreaterThan<long>);
        greater->PushParameterType(this);
        greater->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::GreaterThan, greater);

        const auto lesser = new BuiltInOperation(SyntaxKind::LesserThan, Boolean::Instance(), "clt", LesserThan<long>);
        lesser->PushParameterType(this);
        lesser->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::LesserThan, lesser);

        const auto greaterEquals = new BuiltInOperation(SyntaxKind::GreaterThanEquals, Boolean::Instance(), "clt ldc.i4.0 ceq", GreaterThanEquals<long>);
        greaterEquals->PushParameterType(this);
        greaterEquals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::GreaterThanEquals, greaterEquals);

        const auto lesserEquals = new BuiltInOperation(SyntaxKind::LesserThanEquals, Boolean::Instance(), "cgt ldc.i4.0 ceq", LesserThanEquals<long>);
        lesserEquals->PushParameterType(this);
        lesserEquals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::LesserThanEquals, lesserEquals);

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
        bitwiseXor->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::BitwiseXor, bitwiseXor);

        const auto rightShift = new BuiltInOperation(SyntaxKind::RightShift, this, "shr", RightShift);
        rightShift->PushParameterType(this);
        rightShift->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::RightShift, rightShift);

        const auto leftShift = new BuiltInOperation(SyntaxKind::LeftShift, this, "shl", LeftShift);
        leftShift->PushParameterType(this);
        leftShift->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::LeftShift, leftShift);
    }

    const ICharacteristic* Long::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    const IFunctionDefinition* Long::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        if (name != "TryParse" || ArgumentHash(argumentList) != ArgumentHash(tryParse))
            return nullptr;

        return tryParse;
    }

    const IConstructor* Long::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Long::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Long::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Long::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        return FindBuiltInCast(returnType, fromType);
    }

    const IBuiltInCast* Long::FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });

        for (const auto cast: explicitCasts)
            if (std::get<0>(cast) == hash)
                return std::get<1>(cast);

        return nullptr;
    }

    const IOperatorOverload* Long::FindOverload(const SyntaxKind base) const
    {
        return FindBuiltInOverload(base);
    }
    const IBuiltInOverload* Long::FindBuiltInOverload(const SyntaxKind base) const
    {
        for (const auto cast: overloads)
            if (std::get<0>(cast) == base)
                return std::get<1>(cast);

        return nullptr;
    }

    Long::~Long()
    {
        delete tryParse;

        for (const auto cast: explicitCasts)
            delete std::get<1>(cast);

        for (const auto overload: overloads)
            delete std::get<1>(overload);
    }
}
