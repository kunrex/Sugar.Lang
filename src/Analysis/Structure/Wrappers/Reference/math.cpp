#include "./math.h"

#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_property.h"

#include "../Value/double.h"
#include "../Value/integer.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_math = "[System.Runtime]System.Math";

namespace Analysis::Structure::Wrappers
{
    Math::Math() : Class(cil_math, Describer::PublicStatic), SingletonService()
    { }

    void Math::InitialiseMembers()
    {
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "PI", &Double::Instance(), true, "ldc.r8 3.14159265358979", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "E", &Double::Instance(), true, "ldc.r8 2.71828182845904", false, ""));

        const auto abs = new BuiltInMethod("Abs", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Abs(float64)");
        abs->PushParameterType(&Double::Instance());
        PushFunction(abs);

        const auto max = new BuiltInMethod("Max", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Max(float64, float64)");
        abs->PushParameterType(&Double::Instance());
        abs->PushParameterType(&Double::Instance());
        PushFunction(max);

        const auto min = new BuiltInMethod("Min", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Min(float64, float64)");
        abs->PushParameterType(&Double::Instance());
        abs->PushParameterType(&Double::Instance());
        PushFunction(min);

        const auto sign = new BuiltInMethod("Sign", Describer::PublicStatic, &Integer::Instance(), "call int32 class [System.Runtime]System.Math::Sign(float64)");
        sign->PushParameterType(&Double::Instance());
        PushFunction(sign);

        const auto sqrt = new BuiltInMethod("Sqrt", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Sqrt(float64)");
        sqrt->PushParameterType(&Double::Instance());
        PushFunction(sqrt);

        const auto pow = new BuiltInMethod("Pow", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Pow(float64, float64)");
        pow->PushParameterType(&Double::Instance());
        pow->PushParameterType(&Double::Instance());
        PushFunction(sign);

        const auto exp = new BuiltInMethod("Exp", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Exp(float64)");
        exp->PushParameterType(&Double::Instance());
        PushFunction(exp);

        const auto sin = new BuiltInMethod("Sin", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Sin(float64)");
        sin->PushParameterType(&Double::Instance());
        PushFunction(sin);

        const auto cos = new BuiltInMethod("Cos", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Cos(float64)");
        cos->PushParameterType(&Double::Instance());
        PushFunction(cos);

        const auto tan = new BuiltInMethod("Tan", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::tan(float64)");
        tan->PushParameterType(&Double::Instance());
        PushFunction(tan);

        const auto asin = new BuiltInMethod("Asin", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Asin(float64)");
        asin->PushParameterType(&Double::Instance());
        PushFunction(asin);

        const auto acos = new BuiltInMethod("Acos", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Acos(float64)");
        acos->PushParameterType(&Double::Instance());
        PushFunction(acos);

        const auto atan = new BuiltInMethod("Atan", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Atan(float64)");
        atan->PushParameterType(&Double::Instance());
        PushFunction(atan);

        const auto sinh = new BuiltInMethod("Sinh", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Sinh(float64)");
        sinh->PushParameterType(&Double::Instance());
        PushFunction(sinh);

        const auto cosh = new BuiltInMethod("Cosh", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Cosh(float64)");
        cosh->PushParameterType(&Double::Instance());
        PushFunction(cosh);

        const auto tanh = new BuiltInMethod("Tanh", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Tanh(float64)");
        tanh->PushParameterType(&Double::Instance());
        PushFunction(tanh);

        const auto ln = new BuiltInMethod("Log", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Log(float64)");
        ln->PushParameterType(&Double::Instance());
        PushFunction(ln);

        const auto log = new BuiltInMethod("Log", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Log(float64, float64)");
        log->PushParameterType(&Double::Instance());
        log->PushParameterType(&Double::Instance());
        PushFunction(log);

        const auto round = new BuiltInMethod("Round", Describer::PublicStatic, &Integer::Instance(), "call int32 class [System.Runtime]System.Math::Round(float64, int32)");
        round->PushParameterType(&Double::Instance());
        round->PushParameterType(&Integer::Instance());
        PushFunction(round);

        const auto ceil = new BuiltInMethod("Ceil", Describer::PublicStatic, &Integer::Instance(), "call int32 class [System.Runtime]System.Math::Ceiling(float64)");
        ceil->PushParameterType(&Double::Instance());
        PushFunction(ln);

        const auto floor = new BuiltInMethod("Floor", Describer::PublicStatic, &Integer::Instance(), "call int32 class [System.Runtime]System.Math::Floor(float64)");
        floor->PushParameterType(&Double::Instance());
        PushFunction(floor);
    }
}

