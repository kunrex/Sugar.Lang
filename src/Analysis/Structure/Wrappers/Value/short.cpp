#include "short.h"

#include "integer.h"
#include "long.h"
#include "./float.h"
#include "double.h"
#include "boolean.h"
#include "built_in_functions.h"

#include "../Reference/string.h"
#include "../Generic/referenced.h"

#include "../../DataTypes/data_type_extensions.h"

#include "../../Compilation/compilation_result.h"

#include "../../Context/Constants/integer_constant.h"

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

const string cil_short = "[System.Runtime]System.Int16";

namespace
{
    CompilationResult Addition(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Short::Instance(), std::get<short>(arguments[0].data) + std::get<short>(arguments[1].data)} ; }
    CompilationResult Subtraction(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Short::Instance(), std::get<short>(arguments[0].data) - std::get<short>(arguments[1].data)} ; }
    CompilationResult Multiplication(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Short::Instance(), std::get<short>(arguments[0].data) * std::get<short>(arguments[1].data)} ; }
    CompilationResult Division(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Short::Instance(), std::get<short>(arguments[0].data) / std::get<short>(arguments[1].data)} ; }
    CompilationResult Modulus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Short::Instance(), std::get<short>(arguments[0].data) % std::get<short>(arguments[1].data)} ; }

    CompilationResult Plus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Short::Instance(), arguments[0].data }; }
    CompilationResult Minus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Short::Instance(), -std::get<short>(arguments[0].data) }; }

    CompilationResult Not(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), ~std::get<short>(arguments[0].data)} ; }
    CompilationResult BitwiseAnd(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<short>(arguments[0].data) & std::get<short>(arguments[1].data)} ; }
    CompilationResult BitwiseOr(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<short>(arguments[0].data) | std::get<short>(arguments[1].data)} ; }
    CompilationResult RightShift(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<short>(arguments[0].data) >> std::get<short>(arguments[1].data)} ; }
    CompilationResult LeftShift(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<short>(arguments[0].data) << std::get<short>(arguments[1].data)} ; }
    CompilationResult BitwiseXor(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<short>(arguments[0].data) ^ std::get<short>(arguments[1].data)} ; }
}

namespace Analysis::Structure::Wrappers
{
    Short::Short() : BuiltInValueType(cil_short, Describer::Public), SingletonService(), characteristics()
    { }

    Short Short::instance;

    const Short* Short::Instance() { return &instance; }

    void Short::BindGlobalInstance()
    {
        static bool bound;

        if (!bound)
        {
            instance.BindGlobal();
            bound = true;
        }
    }

    int Short::SlotCount() const { return 1; }

    TypeKind Short::Type() const { return TypeKind::Short; }

    void Short::BindGlobal()
    {
        characteristics[0] = new BuiltInConstant("Max", Describer::Public | Describer::Constexpr, this, new ShortConstant(32767));
        characteristics[1] = new BuiltInConstant("Min", Describer::Public | Describer::Constexpr, this, new ShortConstant(-32767));

        const auto tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, Boolean::Instance(), "bool valuetype [System.Runtime]System.Int16::TryParse(string, int16&)");
        tryParse->PushParameterType(String::Instance());
        tryParse->PushParameterType(Referenced::Instance(this));
        functions[0] = { ArgumentHash(tryParse), tryParse };

        const auto getHash = GetHash();
        functions[1] = { ArgumentHash(getHash), getHash };

        const auto implicitInt = new BuiltInCast(Integer::Instance(), "conv.i4", IntCast<short>);
        implicitInt->PushParameterType(this);
        implicitCasts[0] = { ArgumentHash({ Integer::Instance(), this }), implicitInt };
        explicitCasts[0] = { ArgumentHash({ Integer::Instance(), this }), new BuiltInCast(*implicitInt) };

        const auto implicitLong = new BuiltInCast(Long::Instance(), "conv.i8", LongCast<short>);
        implicitLong->PushParameterType(this);
        implicitCasts[1] = { ArgumentHash({ Long::Instance(), this }), implicitLong };
        explicitCasts[1] =  { ArgumentHash({ Long::Instance(), this }), new BuiltInCast(*implicitLong) };

        const auto implicitFloat = new BuiltInCast(Float::Instance(), "conv.r4", FloatCast<short>);
        implicitFloat->PushParameterType(this);
        implicitCasts[2] =  { ArgumentHash({ Float::Instance(), this }), implicitFloat };
        explicitCasts[2] = { ArgumentHash({ Float::Instance(), this }), new BuiltInCast(*implicitFloat) };

        const auto implicitDouble = new BuiltInCast(Double::Instance(), "conv.r8", DoubleCast<short>);
        implicitDouble->PushParameterType(this);
        implicitCasts[3] =  { ArgumentHash({ Double::Instance(), this }), implicitDouble };
        explicitCasts[3] = { ArgumentHash({ Double::Instance(), this }), new BuiltInCast(*implicitDouble) };

        const auto explicitString = new BuiltInCast(String::Instance(), "call instance string valuetype [System.Runtime]System.Int16::ToString()", StringCast<short>);
        explicitString->PushParameterType(this);
        explicitCasts[4] = { ArgumentHash({ String::Instance(), this }), explicitString };

        const auto equals = new BuiltInOverload(SyntaxKind::Equals, Boolean::Instance(), "ceq", Equals<short>);
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        builtInOverloads[0] = { SyntaxKind::Equals, equals };

        const auto notEquals = new BuiltInOverload(SyntaxKind::NotEquals, Boolean::Instance(), "ceq ldc.i4.0 ceq", NotEquals<short>);
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        builtInOverloads[1] = { SyntaxKind::NotEquals, notEquals };

        const auto addition = new BuiltInOverload(SyntaxKind::Addition, this, "add conv.i2", Addition);
        addition->PushParameterType(this);
        addition->PushParameterType(this);
        builtInOverloads[2] = { SyntaxKind::Addition, addition };

        const auto subtraction = new BuiltInOverload(SyntaxKind::Subtraction, this, "sub conv.i2", Subtraction);
        subtraction->PushParameterType(this);
        subtraction->PushParameterType(this);
        builtInOverloads[3] = { SyntaxKind::Subtraction, subtraction };

        const auto multiplication = new BuiltInOverload(SyntaxKind::Multiplication,this, "mul conv.i2", Multiplication);
        multiplication->PushParameterType(this);
        multiplication->PushParameterType(this);
        builtInOverloads[4] = { SyntaxKind::Multiplication, multiplication };

        const auto division = new BuiltInOverload(SyntaxKind::Division, this, "div conv.i2", Division);
        division->PushParameterType(this);
        division->PushParameterType(this);
        builtInOverloads[5] = { SyntaxKind::Division, division };

        const auto remainder = new BuiltInOverload(SyntaxKind::Modulus, this, "rem conv.i2", Modulus);
        remainder->PushParameterType(this);
        remainder->PushParameterType(this);
        builtInOverloads[6] = { SyntaxKind::Modulus, remainder };

        const auto plus = new BuiltInOverload(SyntaxKind::Plus,this, "nop", Plus);
        plus->PushParameterType(this);
        builtInOverloads[7] = { SyntaxKind::Plus, plus };

        const auto negation = new BuiltInOverload(SyntaxKind::Minus, this, "neg", Minus);
        negation->PushParameterType(this);
        builtInOverloads[8] = { SyntaxKind::Minus, negation };

        const auto increment = new ImplicitOverload(SyntaxKind::Increment, this, "ldc.i2 1 add");
        increment->PushParameterType(this);
        increment->PushParameterType(this);
        overloads[0] = { SyntaxKind::Increment, increment };

        const auto decrement = new ImplicitOverload(SyntaxKind::Decrement, this, "ldc.i2 1 sub");
        decrement->PushParameterType(this);
        decrement->PushParameterType(this);
        overloads[1] = { SyntaxKind::Decrement, decrement };

        const auto greater = new BuiltInOverload(SyntaxKind::GreaterThan, Boolean::Instance(), "cgt", GreaterThan<short>);
        greater->PushParameterType(this);
        greater->PushParameterType(this);
        builtInOverloads[9] = { SyntaxKind::GreaterThan, greater };

        const auto lesser = new BuiltInOverload(SyntaxKind::LesserThan, Boolean::Instance(), "clt", LesserThan<short>);
        lesser->PushParameterType(this);
        lesser->PushParameterType(this);
        builtInOverloads[10] = { SyntaxKind::LesserThan, lesser };

        const auto greaterEquals = new BuiltInOverload(SyntaxKind::GreaterThanEquals, Boolean::Instance(), "clt ldc.i4.0 ceq", GreaterThanEquals<short>);
        greaterEquals->PushParameterType(this);
        greaterEquals->PushParameterType(this);
        builtInOverloads[11] = { SyntaxKind::GreaterThanEquals, greaterEquals };

        const auto lesserEquals = new BuiltInOverload(SyntaxKind::LesserThanEquals, Boolean::Instance(), "cgt ldc.i4.0 ceq", LesserThanEquals<short>);
        lesserEquals->PushParameterType(this);
        lesserEquals->PushParameterType(this);
        builtInOverloads[12] = { SyntaxKind::LesserThanEquals, lesserEquals };

        const auto bitwiseNot = new BuiltInOverload(SyntaxKind::BitwiseNot, Integer::Instance(), "not", Not);
        bitwiseNot->PushParameterType(this);
        builtInOverloads[13] = { SyntaxKind::BitwiseNot, bitwiseNot };

        const auto bitwiseAnd = new BuiltInOverload(SyntaxKind::BitwiseAnd, Integer::Instance(), "and", BitwiseAnd);
        bitwiseAnd->PushParameterType(this);
        bitwiseAnd->PushParameterType(this);
        builtInOverloads[14] = { SyntaxKind::BitwiseAnd, bitwiseAnd };

        const auto bitwiseOr = new BuiltInOverload(SyntaxKind::BitwiseOr, Integer::Instance(), "or", BitwiseOr);
        bitwiseOr->PushParameterType(this);
        bitwiseOr->PushParameterType(this);
        builtInOverloads[15] = { SyntaxKind::BitwiseOr, bitwiseOr };

        const auto bitwiseXor = new BuiltInOverload(SyntaxKind::BitwiseXor, Integer::Instance(), "xor", BitwiseXor);
        bitwiseXor->PushParameterType(this);
        bitwiseXor->PushParameterType(this);
        builtInOverloads[16] = { SyntaxKind::BitwiseXor, bitwiseXor };

        const auto rightShift = new BuiltInOverload(SyntaxKind::RightShift, Integer::Instance(), "shr", RightShift);
        rightShift->PushParameterType(this);
        rightShift->PushParameterType(this);
        builtInOverloads[17] = { SyntaxKind::RightShift, rightShift };

        const auto leftShift = new BuiltInOverload(SyntaxKind::LeftShift, Integer::Instance(), "shl", LeftShift);
        leftShift->PushParameterType(this);
        leftShift->PushParameterType(this);
        builtInOverloads[18] = { SyntaxKind::LeftShift, leftShift };
    }

    const ICharacteristic* Short::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    const IFunctionDefinition* Short::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) & ArgumentHash(argumentList);

        for (const auto function: functions)
            if (function.first == hash)
                return function.second;

        return nullptr;
    }

    const IConstructor* Short::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Short::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Short::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });

        for (const auto cast: implicitCasts)
            if (cast.first == hash)
                return cast.second;

        return nullptr;
    }

    const IFunction* Short::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        return FindBuiltInCast(returnType, fromType);
    }

    const IBuiltInCast* Short::FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });

        for (const auto cast: explicitCasts)
            if (cast.first == hash)
                return cast.second;

        return nullptr;
    }

    const IOperatorOverload* Short::FindOverload(const SyntaxKind base) const
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

    const IBuiltInOverload* Short::FindBuiltInOverload(const SyntaxKind base) const
    {
        for (const auto overload: builtInOverloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    Short::~Short()
    {
        for (const auto characteristic : characteristics)
            delete characteristic;

        for (const auto function: functions)
            delete function.second;

        for (const auto cast: implicitCasts)
            delete cast.second;

        for (const auto cast: explicitCasts)
            delete cast.second;

        for (const auto overload: overloads)
            delete overload.second;

        for (const auto overload: builtInOverloads)
            delete overload.second;
    }
}
