#include "./math.h"

#include "../../DataTypes/data_type_extensions.h"

#include "../Value/double.h"
#include "../Value/integer.h"

#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_property.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

constexpr std::string cil_math = "[System.Runtime]System.Math";

namespace Analysis::Structure::Wrappers
{
    Math::Math() : BuiltInClass(cil_math, Describer::PublicStatic), SingletonService(), characteristics(), functions()
    { }

    TypeKind Math::Type() const { return TypeKind::Math; }

    void Math::InitializeMembers()
    {
        characteristics["PI"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "PI", &Double::Instance(), true, "ldc.r8 3.14159265358979", false, "");
        characteristics["E"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "E", &Double::Instance(), true, "ldc.r8 2.71828182845904", false, "");

        const auto abs = new BuiltInMethod("Abs", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Abs(float64)");
        abs->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Abs") ^ ArgumentHash(abs)] = abs;

        const auto max = new BuiltInMethod("Max", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Max(float64, float64)");
        max->PushParameterType(&Double::Instance());
        max->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Max") ^ ArgumentHash(max)] = max;

        const auto min = new BuiltInMethod("Min", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Min(float64, float64)");
        min->PushParameterType(&Double::Instance());
        min->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Min") ^ ArgumentHash(min)] = min;

        const auto sign = new BuiltInMethod("Sign", Describer::PublicStatic, &Integer::Instance(), "call int32 class [System.Runtime]System.Math::Sign(float64)");
        sign->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Sign") ^ ArgumentHash(sign)] = sign;

        const auto sqrt = new BuiltInMethod("Sqrt", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Sqrt(float64)");
        sqrt->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Sqrt") ^ ArgumentHash(sqrt)] = sqrt;

        const auto pow = new BuiltInMethod("Pow", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Pow(float64, float64)");
        pow->PushParameterType(&Double::Instance());
        pow->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Pow") ^ ArgumentHash(pow)] = pow;

        const auto exp = new BuiltInMethod("Exp", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Exp(float64)");
        exp->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Exp") ^ ArgumentHash(exp)] = exp;

        const auto sin = new BuiltInMethod("Sin", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Sin(float64)");
        sin->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Sin") ^ ArgumentHash(sin)] = sin;

        const auto cos = new BuiltInMethod("Cos", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Cos(float64)");
        cos->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Cos") ^ ArgumentHash(cos)] = cos;

        const auto tan = new BuiltInMethod("Tan", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::tan(float64)");
        tan->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Tan") ^ ArgumentHash(tan)] = tan;

        const auto asin = new BuiltInMethod("Asin", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Asin(float64)");
        asin->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Asin") ^ ArgumentHash(asin)] = asin;

        const auto acos = new BuiltInMethod("Acos", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Acos(float64)");
        acos->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Acos") ^ ArgumentHash(acos)] = acos;

        const auto atan = new BuiltInMethod("Atan", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Atan(float64)");
        atan->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Atan") ^ ArgumentHash(atan)] = atan;

        const auto sinh = new BuiltInMethod("Sinh", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Sinh(float64)");
        sinh->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Sinh") ^ ArgumentHash(sinh)] = sinh;

        const auto cosh = new BuiltInMethod("Cosh", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Cosh(float64)");
        cosh->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Cosh") ^ ArgumentHash(cosh)] = cosh;

        const auto tanh = new BuiltInMethod("Tanh", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Tanh(float64)");
        tanh->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Tanh") ^ ArgumentHash(tanh)] = tanh;

        const auto ln = new BuiltInMethod("Log", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Log(float64)");
        ln->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Log") ^ ArgumentHash(ln)] = ln;

        const auto log = new BuiltInMethod("Log", Describer::PublicStatic, &Double::Instance(), "call float64 class [System.Runtime]System.Math::Log(float64, float64)");
        log->PushParameterType(&Double::Instance());
        log->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Log") ^ ArgumentHash(log)] = log;

        const auto round = new BuiltInMethod("Round", Describer::PublicStatic, &Integer::Instance(), "call int32 class [System.Runtime]System.Math::Round(float64, int32)");
        round->PushParameterType(&Double::Instance());
        round->PushParameterType(&Integer::Instance());
        functions[std::hash<string>()("Round") ^ ArgumentHash(round)] = round;

        const auto ceil = new BuiltInMethod("Ceil", Describer::PublicStatic, &Integer::Instance(), "call int32 class [System.Runtime]System.Math::Ceiling(float64)");
        ceil->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Ceil") ^ ArgumentHash(ceil)] = ceil;

        const auto floor = new BuiltInMethod("Floor", Describer::PublicStatic, &Integer::Instance(), "call int32 class [System.Runtime]System.Math::Floor(float64)");
        floor->PushParameterType(&Double::Instance());
        functions[std::hash<string>()("Floor") ^ ArgumentHash(floor)] = floor;
    }

    const ICharacteristic* Math::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? characteristics.at(name) : nullptr;
    }

    const IFunctionDefinition* Math::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) & ArgumentHash(argumentList);
        return functions.contains(hash) ? nullptr : functions.at(hash);
    }

    const IFunction* Math::FindConstructor(const std::vector<const IDataType*>& argumentList) const
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
            delete characteristic.second;

        for (const auto function: functions)
            delete function.second;
    }
}

