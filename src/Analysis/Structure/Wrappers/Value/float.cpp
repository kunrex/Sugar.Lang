#include "./float.h"

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_operation.h"

#include "short.h"
#include "integer.h"
#include "long.h"
#include "double.h"
#include "boolean.h"
#include "../Reference/string.h"
#include "../Generic/referenced.h"

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_double = "[System.Runtime]System.Single";

namespace Analysis::Structure::Wrappers
{
    Float::Float() : Struct(cil_double, Describer::Public), SingletonService()
    { }

    int Float::SlotCount() const { return 1; }

    void Float::InitialiseMembers()
    {
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Max", &Instance(), true, "ldc.r4 3.4028235E+38", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Min", &Instance(), true, "ldc.r4 -3.4028235E+38", false, ""));

        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "NaN", &Instance(), true, "ldc.r4 NaN", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "PositiveInfinity", &Instance(), true, "ldc.r4 Infinity", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "NegativeInfinity", &Instance(), true, "ldc.r4 -Infinity", false, ""));

        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Epsilon", &Instance(), true, "ldc.r4 1.401298E-45", false, ""));

        const auto tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Single::TryParse(string, float32&)");
        tryParse->PushParameterType(&String::Instance());
        tryParse->PushParameterType(Referenced::Instance(&Instance()));
        PushFunction(tryParse);

        const auto explicitShort = new BuiltInCast(&Short::Instance(), "conv.i2");
        explicitShort->PushParameterType(&Instance());
        PushExplicitCast(explicitShort);

        const auto explicitInteger = new BuiltInCast(&Integer::Instance(), "conv.i4");
        explicitInteger->PushParameterType(&Instance());
        PushExplicitCast(explicitInteger);

        const auto explicitLong = new BuiltInCast(&Long::Instance(), "conv.i8");
        explicitLong->PushParameterType(&Instance());
        PushExplicitCast(explicitLong);

        const auto implicitDouble = new BuiltInCast(&Double::Instance(), "conv.r8");
        implicitDouble->PushParameterType(&Instance());
        PushImplicitCast(implicitDouble);

        const auto explicitString = new BuiltInCast(&String::Instance(), "call instance string valuetype [System.Runtime]System.Single::ToString()");
        explicitString->PushParameterType(&Instance());
        PushExplicitCast(explicitString);

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, &Boolean::Instance(), "ceq");
        equals->PushParameterType(&Instance());
        equals->PushParameterType(&Instance());
        PushOverload(equals);

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, &Boolean::Instance(), "ceq ldc.i4.0 ceq");
        notEquals->PushParameterType(&Instance());
        notEquals->PushParameterType(&Instance());
        PushOverload(notEquals);

        const auto addition = new BuiltInOperation(SyntaxKind::Addition, &Instance(), "add");
        addition->PushParameterType(&Instance());
        addition->PushParameterType(&Instance());
        PushOverload(addition);

        const auto subtraction = new BuiltInOperation(SyntaxKind::Subtraction, &Instance(), "sub");
        subtraction->PushParameterType(&Instance());
        subtraction->PushParameterType(&Instance());
        PushOverload(subtraction);

        const auto multiplication = new BuiltInOperation(SyntaxKind::Multiplication, &Instance(), "mul");
        multiplication->PushParameterType(&Instance());
        multiplication->PushParameterType(&Instance());
        PushOverload(multiplication);

        const auto division = new BuiltInOperation(SyntaxKind::Division, &Instance(), "div");
        division->PushParameterType(&Instance());
        division->PushParameterType(&Instance());
        PushOverload(division);

        const auto remainder = new BuiltInOperation(SyntaxKind::Modulus, &Instance(), "rem");
        remainder->PushParameterType(&Instance());
        remainder->PushParameterType(&Instance());
        PushOverload(remainder);

        const auto negation = new BuiltInOperation(SyntaxKind::Minus, &Instance(), "neg");
        negation->PushParameterType(&Instance());
        PushOverload(negation);

        const auto increment = new BuiltInOperation(SyntaxKind::Increment, &Instance(), "ldc.r8 1.0 add");
        increment->PushParameterType(&Instance());
        increment->PushParameterType(&Instance());
        PushOverload(increment);

        const auto decrement = new BuiltInOperation(SyntaxKind::Decrement, &Instance(), "ldc.r8 1.0 sub");
        decrement->PushParameterType(&Instance());
        decrement->PushParameterType(&Instance());
        PushOverload(remainder);

        const auto incrementPrefix = new BuiltInOperation(SyntaxKind::IncrementPrefix, &Instance(), "ldc.r8 1.0 add");
        incrementPrefix->PushParameterType(&Instance());
        incrementPrefix->PushParameterType(&Instance());
        PushOverload(incrementPrefix);

        const auto decrementPrefix = new BuiltInOperation(SyntaxKind::DecrementPrefix, &Instance(), "ldc.r8 1.0 sub");
        decrementPrefix->PushParameterType(&Instance());
        decrementPrefix->PushParameterType(&Instance());
        PushOverload(decrementPrefix);

        const auto greater = new BuiltInOperation(SyntaxKind::GreaterThan, &Boolean::Instance(), "cgt");
        greater->PushParameterType(&Instance());
        greater->PushParameterType(&Instance());
        PushOverload(equals);

        const auto lesser = new BuiltInOperation(SyntaxKind::LesserThan, &Boolean::Instance(), "clt");
        lesser->PushParameterType(&Instance());
        lesser->PushParameterType(&Instance());
        PushOverload(lesser);

        const auto greaterEquals = new BuiltInOperation(SyntaxKind::GreaterThanEquals, &Boolean::Instance(), "clt ldc.i4.0 ceq");
        greaterEquals->PushParameterType(&Instance());
        greaterEquals->PushParameterType(&Instance());
        PushOverload(greaterEquals);

        const auto lesserEquals = new BuiltInOperation(SyntaxKind::LesserThanEquals, &Boolean::Instance(), "cgt ldc.i4.0 ceq");
        lesserEquals->PushParameterType(&Instance());
        lesserEquals->PushParameterType(&Instance());
        PushOverload(lesserEquals);
    }
}

