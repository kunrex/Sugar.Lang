#include "integer.h"

#include "short.h"
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

namespace
{
    CompilationResult Addition(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<int>(arguments[0].data) + std::get<int>(arguments[1].data)} ; }
    CompilationResult Subtraction(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<int>(arguments[0].data) - std::get<int>(arguments[1].data)} ; }
    CompilationResult Multiplication(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<int>(arguments[0].data) * std::get<int>(arguments[1].data)} ; }
    CompilationResult Division(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<int>(arguments[0].data) / std::get<int>(arguments[1].data)} ; }
    CompilationResult Modulus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<int>(arguments[0].data) % std::get<int>(arguments[1].data)} ; }

    CompilationResult Plus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), arguments[0].data }; }
    CompilationResult Minus(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), -std::get<int>(arguments[0].data) }; }

    CompilationResult Not(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), ~std::get<int>(arguments[0].data)} ; }
    CompilationResult BitwiseAnd(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<int>(arguments[0].data) & std::get<int>(arguments[1].data)} ; }
    CompilationResult BitwiseOr(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<int>(arguments[0].data) | std::get<int>(arguments[1].data)} ; }
    CompilationResult RightShift(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<int>(arguments[0].data) >> std::get<int>(arguments[1].data)} ; }
    CompilationResult LeftShift(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<int>(arguments[0].data) << std::get<int>(arguments[1].data)} ; }
    CompilationResult BitwiseXor(const std::vector<CompilationResult>& arguments) { return { Analysis::Structure::Wrappers::Integer::Instance(), std::get<int>(arguments[0].data) ^ std::get<int>(arguments[1].data)} ; }
}

namespace Analysis::Structure::Wrappers
{
    Integer::Integer() : BuiltInValueType("int32", Describer::Public), SingletonService(), characteristics()
    { }

    Integer Integer::instance;

    const Integer* Integer::Instance() { return &instance; }

    void Integer::BindGlobalInstance()
    {
        static bool bound;

        if (!bound)
        {
            instance.BindGlobal();
            bound = true;
        }
    }

    int Integer::SlotCount() const { return 1; }

    TypeKind Integer::Type() const { return TypeKind::Int; }

    void Integer::BindGlobal()
    {
        characteristics[0] = new BuiltInConstant("Max", Describer::Public | Describer::Constexpr, this, new IntegerConstant(2147483647));
        characteristics[1] = new BuiltInConstant("Min", Describer::Public | Describer::Constexpr, this, new IntegerConstant(-2147483648));

        const auto tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, Boolean::Instance(), "call bool [System.Runtime]System.Int32::TryParse(string, int32&)");
        tryParse->PushParameterType(String::Instance());
        tryParse->PushParameterType(Referenced::Instance(this));
        functions[0] = { std::hash<string>()(tryParse->Name()) ^ ArgumentHash(tryParse), tryParse };

        const auto getHash = GetHash();
        functions[1] = { std::hash<string>()(getHash->Name()) ^ ArgumentHash(getHash), getHash };

        const auto explicitShort = new BuiltInCast(Short::Instance(), "conv.i2", ShortCast<int>);
        explicitShort->PushParameterType(this);
        explicitCasts[0] = { ArgumentHash({ Short::Instance(), this }), explicitShort };

        const auto implicitLong = new BuiltInCast(Long::Instance(), "conv.i8", LongCast<int>);
        implicitLong->PushParameterType(this);
        implicitCasts[0] = { ArgumentHash({ Long::Instance(), this }), implicitLong };
        explicitCasts[1] = { ArgumentHash({ Long::Instance(), this }), new BuiltInCast(*implicitLong) };

        const auto explicitFloat = new BuiltInCast(Float::Instance(), "conv.r4", FloatCast<int>);
        explicitFloat->PushParameterType(this);
        explicitCasts[2] = { ArgumentHash({ Float::Instance(), this }), explicitFloat };

        const auto implicitDouble = new BuiltInCast(Double::Instance(), "conv.r8", DoubleCast<int>);
        implicitDouble->PushParameterType(this);
        implicitCasts[1] =  { ArgumentHash({ Double::Instance(), this }), implicitDouble };
        explicitCasts[3] = { ArgumentHash({ Double::Instance(), this}), new BuiltInCast(*implicitDouble) };

        const auto explicitString = new BuiltInCast(String::Instance(), "call instance string [System.Runtime]System.Int32::ToString()", StringCast<long>);
        explicitString->PushParameterType(this);
        explicitCasts[4] = { ArgumentHash({ String::Instance(), this }), explicitString };

        const auto equals = new BuiltInOverload(SyntaxKind::Equals, Boolean::Instance(), "ceq", Equals<int>);
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        builtInOverloads[0] = { SyntaxKind::Equals, equals };

        const auto notEquals = new BuiltInOverload(SyntaxKind::NotEquals, Boolean::Instance(), "ceq ldc.i4.0 ceq", NotEquals<int>);
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

        const auto remainder = new BuiltInOverload(SyntaxKind::Modulus, this, "rem", Modulus);
        remainder->PushParameterType(this);
        remainder->PushParameterType(this);
        builtInOverloads[6] = { SyntaxKind::Modulus, remainder };

        const auto plus = new BuiltInOverload(SyntaxKind::Plus,this, "nop", Plus);
        plus->PushParameterType(this);
        builtInOverloads[7] = { SyntaxKind::Plus, plus };

        const auto negation = new BuiltInOverload(SyntaxKind::Minus, this, "neg", Minus);
        negation->PushParameterType(this);
        builtInOverloads[8] = { SyntaxKind::Minus, negation };

        const auto increment = new GeneratedOverload(SyntaxKind::Increment, this, "ldc.i4 1 add");
        increment->PushParameterType(this);
        increment->PushParameterType(this);
        overloads[0] = { SyntaxKind::Increment, increment };

        const auto decrement = new GeneratedOverload(SyntaxKind::Decrement, this, "ldc.i4 1 sub");
        decrement->PushParameterType(this);
        decrement->PushParameterType(this);
        overloads[1] = { SyntaxKind::Decrement, decrement };

        const auto greater = new BuiltInOverload(SyntaxKind::GreaterThan, Boolean::Instance(), "cgt", GreaterThan<int>);
        greater->PushParameterType(this);
        greater->PushParameterType(this);
        builtInOverloads[9] = { SyntaxKind::GreaterThan, greater };

        const auto lesser = new BuiltInOverload(SyntaxKind::LesserThan, Boolean::Instance(), "clt", LesserThan<int>);
        lesser->PushParameterType(this);
        lesser->PushParameterType(this);
        builtInOverloads[10] = { SyntaxKind::LesserThan, lesser };

        const auto greaterEquals = new BuiltInOverload(SyntaxKind::GreaterThanEquals, Boolean::Instance(), "clt ldc.i4.0 ceq", GreaterThanEquals<int>);
        greaterEquals->PushParameterType(this);
        greaterEquals->PushParameterType(this);
        builtInOverloads[11] = { SyntaxKind::GreaterThanEquals, greaterEquals };

        const auto lesserEquals = new BuiltInOverload(SyntaxKind::LesserThanEquals, Boolean::Instance(), "cgt ldc.i4.0 ceq", LesserThanEquals<int>);
        lesserEquals->PushParameterType(this);
        lesserEquals->PushParameterType(this);
        builtInOverloads[12] = { SyntaxKind::LesserThanEquals, lesserEquals };

        const auto bitwiseNot = new BuiltInOverload(SyntaxKind::BitwiseNot, this, "not", Not);
        bitwiseNot->PushParameterType(this);
        builtInOverloads[13] = { SyntaxKind::BitwiseNot, bitwiseNot };

        const auto bitwiseAnd = new BuiltInOverload(SyntaxKind::BitwiseAnd, this, "and", BitwiseAnd);
        bitwiseAnd->PushParameterType(this);
        bitwiseAnd->PushParameterType(this);
        builtInOverloads[14] = { SyntaxKind::BitwiseAnd, bitwiseAnd };

        const auto bitwiseOr = new BuiltInOverload(SyntaxKind::BitwiseOr, this, "or", BitwiseOr);
        bitwiseOr->PushParameterType(this);
        bitwiseOr->PushParameterType(this);
        builtInOverloads[15] = { SyntaxKind::BitwiseOr, bitwiseOr };

        const auto bitwiseXor = new BuiltInOverload(SyntaxKind::BitwiseXor, this, "xor", BitwiseXor);
        bitwiseXor->PushParameterType(this);
        bitwiseXor->PushParameterType(this);
        builtInOverloads[16] = { SyntaxKind::BitwiseXor, bitwiseXor };

        const auto rightShift = new BuiltInOverload(SyntaxKind::RightShift, this, "shr", RightShift);
        rightShift->PushParameterType(this);
        rightShift->PushParameterType(this);
        builtInOverloads[17] = { SyntaxKind::RightShift, rightShift };

        const auto leftShift = new BuiltInOverload(SyntaxKind::LeftShift, this, "shl", LeftShift);
        leftShift->PushParameterType(this);
        leftShift->PushParameterType(this);
        builtInOverloads[18] = { SyntaxKind::LeftShift, leftShift };
    }

    const ICharacteristic* Integer::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    const IFunctionDefinition* Integer::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) & ArgumentHash(argumentList);

        for (const auto function: functions)
            if (function.first == hash)
                return function.second;

        return nullptr;
    }

    const IConstructor* Integer::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Integer::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Integer::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });

        for (const auto cast: explicitCasts)
            if (cast.first == hash)
                return cast.second;

        return nullptr;
    }

    const IFunction* Integer::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        return FindBuiltInCast(returnType, fromType);
    }

    const IBuiltInCast* Integer::FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });

        for (const auto cast: explicitCasts)
            if (cast.first == hash)
                return cast.second;

        return nullptr;
    }

    const IOperatorOverload* Integer::FindOverload(const SyntaxKind base) const
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

    const IBuiltInOverload* Integer::FindBuiltInOverload(const SyntaxKind base) const
    {
        for (const auto overload: builtInOverloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    Integer::~Integer()
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


