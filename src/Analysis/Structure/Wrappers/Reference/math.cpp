#include "./math.h"

#include "../../Nodes/Global/BuiltIn/built_in_method.h"
#include "../../Nodes/Global/BuiltIn/built_in_property.h"

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

        const auto abs = new BuiltInMethod("Abs", Describer::PublicStatic, &Double::Instance());
        abs->PushParameterType(&Double::Instance());
        PushFunction(abs);

        const auto max = new BuiltInMethod("Max", Describer::PublicStatic, &Double::Instance());
        abs->PushParameterType(&Double::Instance());
        abs->PushParameterType(&Double::Instance());
        PushFunction(max);

        const auto min = new BuiltInMethod("Min", Describer::PublicStatic, &Double::Instance());
        abs->PushParameterType(&Double::Instance());
        abs->PushParameterType(&Double::Instance());
        PushFunction(min);

        const auto sign = new BuiltInMethod("Sign", Describer::PublicStatic, &Integer::Instance());
        sign->PushParameterType(&Double::Instance());
        PushFunction(sign);

        const auto sqrt = new BuiltInMethod("Sqrt", Describer::PublicStatic, &Double::Instance());
        sqrt->PushParameterType(&Double::Instance());
        PushFunction(sqrt);

        const auto pow = new BuiltInMethod("Pow", Describer::PublicStatic, &Double::Instance());
        pow->PushParameterType(&Double::Instance());
        pow->PushParameterType(&Double::Instance());
        PushFunction(sign);

        const auto exp = new BuiltInMethod("Exp", Describer::PublicStatic, &Double::Instance());
        exp->PushParameterType(&Double::Instance());
        PushFunction(exp);

        const auto sin = new BuiltInMethod("Sin", Describer::PublicStatic, &Double::Instance());
        sin->PushParameterType(&Double::Instance());
        PushFunction(sin);

        const auto cos = new BuiltInMethod("Exp", Describer::PublicStatic, &Double::Instance());
        cos->PushParameterType(&Double::Instance());
        PushFunction(cos);

        const auto tan = new BuiltInMethod("Exp", Describer::PublicStatic, &Double::Instance());
        tan->PushParameterType(&Double::Instance());
        PushFunction(tan);

        const auto asin = new BuiltInMethod("Asin", Describer::PublicStatic, &Double::Instance());
        asin->PushParameterType(&Double::Instance());
        PushFunction(asin);

        const auto acos = new BuiltInMethod("Acos", Describer::PublicStatic, &Double::Instance());
        acos->PushParameterType(&Double::Instance());
        PushFunction(acos);

        const auto atan = new BuiltInMethod("Atan", Describer::PublicStatic, &Double::Instance());
        atan->PushParameterType(&Double::Instance());
        PushFunction(atan);

        const auto sinh = new BuiltInMethod("Sinh", Describer::PublicStatic, &Double::Instance());
        sinh->PushParameterType(&Double::Instance());
        PushFunction(sinh);

        const auto cosh = new BuiltInMethod("Cosh", Describer::PublicStatic, &Double::Instance());
        cosh->PushParameterType(&Double::Instance());
        PushFunction(cosh);

        const auto tanh = new BuiltInMethod("Tanh", Describer::PublicStatic, &Double::Instance());
        tanh->PushParameterType(&Double::Instance());
        PushFunction(tanh);

        const auto ln = new BuiltInMethod("Log", Describer::PublicStatic, &Double::Instance());
        ln->PushParameterType(&Double::Instance());
        PushFunction(ln);

        const auto log = new BuiltInMethod("Log", Describer::PublicStatic, &Double::Instance());
        log->PushParameterType(&Double::Instance());
        log->PushParameterType(&Double::Instance());
        PushFunction(log);

        const auto round = new BuiltInMethod("Round", Describer::PublicStatic, &Integer::Instance());
        round->PushParameterType(&Double::Instance());
        round->PushParameterType(&Integer::Instance());
        PushFunction(round);

        const auto ceil = new BuiltInMethod("Ceiling", Describer::PublicStatic, &Integer::Instance());
        ceil->PushParameterType(&Double::Instance());
        PushFunction(ln);

        const auto floor = new BuiltInMethod("Floor", Describer::PublicStatic, &Integer::Instance());
        floor->PushParameterType(&Double::Instance());
        PushFunction(floor);
    }
}

