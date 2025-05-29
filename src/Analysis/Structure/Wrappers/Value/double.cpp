#include "double.h"

#include "../../DataTypes/data_type_extensions.h"

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

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_constant.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_operation.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_double = "[System.Runtime]System.Double";

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
    Double::Double() : BuiltInValueType(cil_double, Describer::Public), SingletonService(), tryParse(nullptr), explicitCasts(), overloads()
    {
        BindGlobal();
    }

    const Double* Double::Instance()
    {
        static const Double instance;
        return &instance;
    }

    int Double::SlotCount() const { return 2; }

    TypeKind Double::Type() const { return TypeKind::Double; }

    void Double::BindGlobal()
    {
        characteristics.push_back(new BuiltInConstant("Max", Describer::Public | Describer::Constexpr, this, new DoubleConstant(1.7976931348623157E+308)));
        characteristics.push_back(new BuiltInConstant("Min", Describer::Public | Describer::Constexpr, this, new DoubleConstant(-1.7976931348623157E+308)));

        characteristics.push_back(new BuiltInProperty("NaN", Describer::PublicStatic | Describer::Const, this, true, "ldc.r4 NaN", false, ""));
        characteristics.push_back(new BuiltInProperty("PositiveInfinity", Describer::PublicStatic | Describer::Const, this, true, "ldc.r4 Infinity", false, ""));
        characteristics.push_back(new BuiltInProperty("NegativeInfinity", Describer::PublicStatic | Describer::Const, this, true, "ldc.r4 -Infinity", false, ""));

        characteristics.push_back(new BuiltInConstant("Epsilon", Describer::Public | Describer::Constexpr, this, new FloatConstant(4.94065645841247E-324)));

        tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, Boolean::Instance(), "bool valuetype [System.Runtime]System.Double::TryParse(string, float64&)");
        tryParse->PushParameterType(String::Instance());
        tryParse->PushParameterType(Referenced::Instance(this));

        const auto explicitShort = new BuiltInCast(Short::Instance(), "conv.i2", ShortCast<double>);
        explicitShort->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ Short::Instance(), this }), explicitShort);

        const auto explicitInteger = new BuiltInCast(Integer::Instance(), "conv.i4", IntCast<double>);
        explicitInteger->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ Integer::Instance(), this }), explicitInteger);

        const auto explicitLong = new BuiltInCast(Long::Instance(), "conv.i8", LongCast<double>);
        explicitLong->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ Long::Instance(), this }), explicitLong);

        const auto explicitFloat = new BuiltInCast(Float::Instance(), "conv.r4", FloatCast<double>);
        explicitFloat->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ Float::Instance(), this }), explicitFloat);

        const auto explicitString = new BuiltInCast(String::Instance(), "call instance string valuetype [System.Runtime]System.Double::ToString()", StringCast<double>);
        explicitString->PushParameterType(this);
        explicitCasts.emplace_back(ArgumentHash({ String::Instance(), this }), explicitShort);

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, Boolean::Instance(), "ceq", Equals<double>);
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Equals, equals);

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, Boolean::Instance(), "ceq ldc.i4.0 ceq", NotEquals<double>);
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

        const auto greater = new BuiltInOperation(SyntaxKind::GreaterThan, Boolean::Instance(), "cgt", GreaterThan<double>);
        greater->PushParameterType(this);
        greater->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::GreaterThan, greater);

        const auto lesser = new BuiltInOperation(SyntaxKind::LesserThan, Boolean::Instance(), "clt", LesserThan<double>);
        lesser->PushParameterType(this);
        lesser->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::LesserThan, lesser);

        const auto greaterEquals = new BuiltInOperation(SyntaxKind::GreaterThanEquals, Boolean::Instance(), "clt ldc.i4.0 ceq", GreaterThanEquals<double>);
        greaterEquals->PushParameterType(this);
        greaterEquals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::GreaterThanEquals, greaterEquals);

        const auto lesserEquals = new BuiltInOperation(SyntaxKind::LesserThanEquals, Boolean::Instance(), "cgt ldc.i4.0 ceq", LesserThanEquals<double>);
        lesserEquals->PushParameterType(this);
        lesserEquals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::LesserThanEquals, lesserEquals);
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
        if (name != "TryParse" || ArgumentHash(argumentList) != ArgumentHash(tryParse))
            return nullptr;

        return tryParse;
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
            if (std::get<0>(cast) == hash)
                return std::get<1>(cast);

        return nullptr;
    }

    const IOperatorOverload* Double::FindOverload(const SyntaxKind base) const
    {
        return FindBuiltInOverload(base);
    }

    const IBuiltInOverload* Double::FindBuiltInOverload(const SyntaxKind base) const
    {
        for (const auto cast: overloads)
            if (std::get<0>(cast) == base)
                return std::get<1>(cast);

        return nullptr;
    }

    Double::~Double()
    {
        delete tryParse;

        for (const auto cast: explicitCasts)
            delete std::get<1>(cast);

        for (const auto overload: overloads)
            delete std::get<1>(overload);
    }
}
