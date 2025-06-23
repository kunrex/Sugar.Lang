#include "./math.h"

#include "../Value/double.h"
#include "../Value/integer.h"

#include "../../Context/Constants/float_constant.h"
#include "../../DataTypes/data_type_extensions.h"

#include "../../Global/Functions/method_function.h"
#include "../../Global/Variables/global_constant.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Context;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_math = "[System.Runtime]System.Math";

namespace Analysis::Structure::Wrappers
{
    Math::Math() : BuiltInClass(cil_math, Describer::PublicStatic), SingletonService(), characteristics(), functions()
    { }

    Math Math::instance;

    const Math* Math::Instance() { return &instance; }

    void Math::BindGlobalInstance()
    {
        static bool bound;

        if (!bound)
        {
            instance.BindGlobal();
            bound = true;
        }
    }

    TypeKind Math::Type() const { return TypeKind::Math; }

    void Math::BindGlobal()
    {
        characteristics[0] = new BuiltInConstant("E", Describer::Public | Describer::Constexpr, Double::Instance(), new DoubleConstant(M_E));
        characteristics[1] = new BuiltInConstant("PI", Describer::Public | Describer::Constexpr, Double::Instance(), new DoubleConstant(M_PI));

        const auto abs = new BuiltInMethod("Abs", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Abs(float64)");
        abs->PushParameterType(Double::Instance());
        functions[0] = { std::hash<string>()(abs->Name()) ^ ArgumentHash(abs), abs };

        const auto max = new BuiltInMethod("Max", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Max(float64, float64)");
        max->PushParameterType(Double::Instance());
        max->PushParameterType(Double::Instance());
        functions[1] = { std::hash<string>()(max->Name()) ^ ArgumentHash(max), max };

        const auto min = new BuiltInMethod("Min", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Min(float64, float64)");
        min->PushParameterType(Double::Instance());
        min->PushParameterType(Double::Instance());
        functions[2] = { std::hash<string>()(min->Name()) ^ ArgumentHash(min), min };

        const auto sign = new BuiltInMethod("Sign", Describer::PublicStatic, Integer::Instance(), "call int32 [System.Runtime]System.Math::Sign(float64)");
        sign->PushParameterType(Double::Instance());
        functions[3] = { std::hash<string>()(sign->Name()) ^ ArgumentHash(sign), sign };

        const auto sqrt = new BuiltInMethod("Sqrt", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Sqrt(float64)");
        sqrt->PushParameterType(Double::Instance());
        functions[4] = { std::hash<string>()(sqrt->Name()) ^ ArgumentHash(sqrt), sqrt };

        const auto pow = new BuiltInMethod("Pow", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Pow(float64, float64)");
        pow->PushParameterType(Double::Instance());
        pow->PushParameterType(Double::Instance());
        functions[5] = { std::hash<string>()(pow->Name()) ^ ArgumentHash(pow), pow };

        const auto exp = new BuiltInMethod("Exp", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Exp(float64)");
        exp->PushParameterType(Double::Instance());
        functions[6] = { std::hash<string>()(exp->Name()) ^ ArgumentHash(exp), exp };

        const auto sin = new BuiltInMethod("Sin", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Sin(float64)");
        sin->PushParameterType(Double::Instance());
        functions[7] = { std::hash<string>()(sin->Name()) ^ ArgumentHash(sin), sin };

        const auto cos = new BuiltInMethod("Cos", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Cos(float64)");
        cos->PushParameterType(Double::Instance());
        functions[8] = { std::hash<string>()(cos->Name()) ^ ArgumentHash(cos), cos };

        const auto tan = new BuiltInMethod("Tan", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::tan(float64)");
        tan->PushParameterType(Double::Instance());
        functions[9] = { std::hash<string>()(tan->Name()) ^ ArgumentHash(tan), tan };

        const auto asin = new BuiltInMethod("Asin", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Asin(float64)");
        asin->PushParameterType(Double::Instance());
        functions[10] = { std::hash<string>()(asin->Name()) ^ ArgumentHash(asin), asin };

        const auto acos = new BuiltInMethod("Acos", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Acos(float64)");
        acos->PushParameterType(Double::Instance());
        functions[11] = { std::hash<string>()(acos->Name()) ^ ArgumentHash(acos), acos };

        const auto atan = new BuiltInMethod("Atan", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Atan(float64)");
        atan->PushParameterType(Double::Instance());
        functions[12] = { std::hash<string>()(atan->Name()) ^ ArgumentHash(atan), atan };

        const auto sinh = new BuiltInMethod("Sinh", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Sinh(float64)");
        sinh->PushParameterType(Double::Instance());
        functions[13] = { std::hash<string>()(sinh->Name()) ^ ArgumentHash(sinh), sinh };

        const auto cosh = new BuiltInMethod("Cosh", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Cosh(float64)");
        cosh->PushParameterType(Double::Instance());
        functions[14] = { std::hash<string>()(cosh->Name()) ^ ArgumentHash(cosh), cosh };

        const auto tanh = new BuiltInMethod("Tanh", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Tanh(float64)");
        tanh->PushParameterType(Double::Instance());
        functions[15] = { std::hash<string>()(tanh->Name()) ^ ArgumentHash(tanh), tanh };

        const auto ln = new BuiltInMethod("Log", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Log(float64)");
        ln->PushParameterType(Double::Instance());
        functions[16] = { std::hash<string>()(ln->Name()) ^ ArgumentHash(ln), ln };

        const auto log = new BuiltInMethod("Log", Describer::PublicStatic, Double::Instance(), "call float64 [System.Runtime]System.Math::Log(float64, float64)");
        log->PushParameterType(Double::Instance());
        log->PushParameterType(Double::Instance());
        functions[17] = { std::hash<string>()(log->Name()) ^ ArgumentHash(log), log };

        const auto round = new BuiltInMethod("Round", Describer::PublicStatic, Integer::Instance(), "call int32 [System.Runtime]System.Math::Round(float64, int32)");
        round->PushParameterType(Double::Instance());
        round->PushParameterType(Integer::Instance());
        functions[18] = { std::hash<string>()(round->Name()) ^ ArgumentHash(round), round };

        const auto ceil = new BuiltInMethod("Ceil", Describer::PublicStatic, Integer::Instance(), "call int32 [System.Runtime]System.Math::Ceiling(float64)");
        ceil->PushParameterType(Double::Instance());
        functions[19] = { std::hash<string>()(ceil->Name()) ^ ArgumentHash(ceil), ceil };

        const auto floor = new BuiltInMethod("Floor", Describer::PublicStatic, Integer::Instance(), "call int32 [System.Runtime]System.Math::Floor(float64)");
        floor->PushParameterType(Double::Instance());
        functions[20] = { std::hash<string>()(floor->Name()) ^ ArgumentHash(floor), floor };
    }

    const ICharacteristic* Math::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    const IFunctionDefinition* Math::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) & ArgumentHash(argumentList);

        for (const auto function: functions)
            if (function.first == hash)
                return function.second;

        return nullptr;
    }

    const IConstructor* Math::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Math::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Math::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Math::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* Math::FindOverload(const SyntaxKind base) const
    { return nullptr; }

    Math::~Math()
    {
        for (const auto characteristic: characteristics)
            delete characteristic;

        for (const auto function: functions)
            delete function.second;
    }
}

