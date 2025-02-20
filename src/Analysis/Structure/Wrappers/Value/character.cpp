#include "character.h"

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_operation.h"

#include "short.h"
#include "integer.h"
#include "long.h"
#include "boolean.h"
#include "../Reference/string.h"

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_boolean = "[System.Runtime]System.Char";

namespace Analysis::Structure::Wrappers
{
    Character::Character() : Struct(cil_boolean, Describer::Public), SingletonService()
    { }

    int Character::SlotCount() const { return 1; }

    void Character::InitialiseMembers()
    {
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "MinValue", &Instance(), true, "ldsfld char System.Char::MinValue", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "MaxValue", &Instance(), true, "ldsfld char System.Char::MaxValue", false, ""));

        const auto isDigit = new BuiltInMethod("IsDigit", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsDigit(char)");
        isDigit->PushParameterType(&Boolean::Instance());
        PushFunction(isDigit);

        const auto isLetter = new BuiltInMethod("IsLetter", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsLetter(char)");
        isDigit->PushParameterType(&Boolean::Instance());
        PushFunction(isLetter);

        const auto isDigitOrLetter = new BuiltInMethod("IsLetterOrDigit", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsLetterOrDigit(char)");
        isDigit->PushParameterType(&Boolean::Instance());
        PushFunction(isDigitOrLetter);

        const auto isWhiteSpace = new BuiltInMethod("IsWhiteSpace", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsWhiteSpace(char)");
        isDigit->PushParameterType(&Boolean::Instance());
        PushFunction(isWhiteSpace);

        const auto isPunctuation = new BuiltInMethod("IsPunctuation", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsPunctuation(char)");
        isDigit->PushParameterType(&Boolean::Instance());
        PushFunction(isPunctuation);

        const auto toUpper = new BuiltInMethod("ToUpper()", Describer::Public, &Instance(), "instance char valuetype [System.Runtime]System.Char::ToUpper()");
        PushFunction(toUpper);

        const auto toLower = new BuiltInMethod("ToLower()", Describer::Public, &Instance(), "instance char valuetype [System.Runtime]System.Char::ToLower()");
        PushFunction(toLower);

        const auto implicitInteger = new BuiltInCast(&Integer::Instance(), "conv.i4");
        implicitInteger->PushParameterType(&Instance());
        PushImplicitCast(implicitInteger);

        const auto explicitShort = new BuiltInCast(&Short::Instance(), "conv.i2");
        explicitShort->PushParameterType(&Instance());
        PushExplicitCast(explicitShort);

        const auto explicitLong = new BuiltInCast(&Long::Instance(), "conv.i8");
        explicitLong->PushParameterType(&Instance());
        PushExplicitCast(explicitLong);

        const auto implicitString = new BuiltInCast(&String::Instance(), "call instance string valuetype [System.Runtime]System.Char::ToString()");
        implicitString->PushParameterType(&Instance());
        PushImplicitCast(implicitString);

        const auto explicitString = new BuiltInCast(&String::Instance(), "call instance string valuetype [System.Runtime]System.Char::ToString()");
        explicitLong->PushParameterType(&Instance());
        PushExplicitCast(explicitString);

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, &Instance(), "ceq");
        equals->PushParameterType(&Instance());
        equals->PushParameterType(&Instance());
        PushOverload(equals);

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, &Instance(), "ceq ldc.i4.0 ceq");
        notEquals->PushParameterType(&Instance());
        notEquals->PushParameterType(&Instance());
        PushOverload(notEquals);
    }
}

