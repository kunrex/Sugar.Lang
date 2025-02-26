#include "short.h"

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_operation.h"

#include "integer.h"
#include "long.h"
#include "./float.h"
#include "double.h"
#include "boolean.h"
#include "../Reference/string.h"
#include "../Generic/referenced.h"

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_double = "[System.Runtime]System.Int16";

namespace Analysis::Structure::Wrappers
{
    Short::Short() : ValueType(cil_double, Describer::Public), SingletonService()
    { }

    int Short::SlotCount() const { return 1; }

    void Short::InitialiseMembers()
    {
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Max", &Instance(), true, "ldc.i2 32767", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Min", &Instance(), true, "ldc.i2 -32767", false, ""));

        const auto tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Int16::TryParse(string, int16&)");
        tryParse->PushParameterType(&String::Instance());
        tryParse->PushParameterType(Referenced::Instance(&Instance()));
        PushFunction(tryParse);

        const auto explicitInt = new BuiltInCast(&Integer::Instance(), "conv.i4");
        explicitInt->PushParameterType(&Instance());
        PushExplicitCast(explicitInt);

        const auto explicitLong = new BuiltInCast(&Long::Instance(), "conv.i8");
        explicitLong->PushParameterType(&Instance());
        PushExplicitCast(explicitLong);

        const auto explicitFloat = new BuiltInCast(&Float::Instance(), "conv.r4");
        explicitFloat->PushParameterType(&Instance());
        PushExplicitCast(explicitFloat);

        const auto explicitDouble = new BuiltInCast(&Double::Instance(), "conv.r8");
        explicitDouble->PushParameterType(&Instance());
        PushExplicitCast(explicitDouble);

        const auto explicitString = new BuiltInCast(&String::Instance(), "call instance string valuetype [System.Runtime]System.Int16::ToString()");
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

        const auto bitwiseNot = new BuiltInOperation(SyntaxKind::BitwiseNot, &Instance(), "not");
        bitwiseNot->PushParameterType(&Instance());
        PushOverload(bitwiseNot);

        const auto bitwiseAnd = new BuiltInOperation(SyntaxKind::BitwiseAnd, &Instance(), "and");
        bitwiseAnd->PushParameterType(&Instance());
        bitwiseAnd->PushParameterType(&Instance());
        PushOverload(bitwiseAnd);

        const auto bitwiseOr = new BuiltInOperation(SyntaxKind::BitwiseOr, &Instance(), "or");
        bitwiseOr->PushParameterType(&Instance());
        bitwiseOr->PushParameterType(&Instance());
        PushOverload(bitwiseOr);

        const auto bitwiseXor = new BuiltInOperation(SyntaxKind::BitwiseXor, &Instance(), "xor");
        bitwiseXor->PushParameterType(&Instance());
        bitwiseXor->PushParameterType(&Instance());
        PushOverload(bitwiseXor);

        const auto rightShift = new BuiltInOperation(SyntaxKind::RightShift, &Instance(), "shr");
        rightShift->PushParameterType(&Instance());
        rightShift->PushParameterType(&Instance());
        PushOverload(rightShift);

        const auto leftShift = new BuiltInOperation(SyntaxKind::LeftShift, &Instance(), "shl");
        leftShift->PushParameterType(&Instance());
        leftShift->PushParameterType(&Instance());
        PushOverload(leftShift);
    }
}
