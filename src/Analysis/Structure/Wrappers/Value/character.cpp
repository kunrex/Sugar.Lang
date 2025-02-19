#include "character.h"

#include "../../Nodes/Global/BuiltIn/built_in_cast.h"
#include "../../Nodes/Global/BuiltIn/built_in_method.h"
#include "../../Nodes/Global/BuiltIn/built_in_property.h"

#include "short.h"
#include "integer.h"
#include "long.h"
#include "./float.h"
#include "boolean.h"
#include "double.h"
#include "../Reference/string.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_character = "[System.Runtime]System.Char";

namespace Analysis::Structure::Wrappers
{
    Character::Character() : Struct(cil_character, Describer::Public), SingletonService()
    { }

    void Character::InitialiseMembers()
    {
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "MinValue", &Instance(), true, "ldsfld char System.Char::MinValue", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "MaxValue", &Instance(), true, "ldsfld char System.Char::MaxValue", false, ""));

        const auto isDigit = new BuiltInMethod("IsDigit", Describer::PublicStatic, &Boolean::Instance());
        isDigit->PushParameterType(&Instance());
        PushFunction(isDigit);

        const auto isLetter = new BuiltInMethod("IsLetter", Describer::PublicStatic, &Boolean::Instance());
        isDigit->PushParameterType(&Instance());
        PushFunction(isLetter);

        const auto isDigitOrLetter = new BuiltInMethod("IsLetterOrDigit", Describer::PublicStatic, &Boolean::Instance());
        isDigit->PushParameterType(&Instance());
        PushFunction(isDigitOrLetter);

        const auto isWhiteSpace = new BuiltInMethod("IsWhiteSpace", Describer::PublicStatic, &Boolean::Instance());
        isDigit->PushParameterType(&Instance());
        PushFunction(isWhiteSpace);

        const auto isPunctuation = new BuiltInMethod("IsPunctuation", Describer::PublicStatic, &Boolean::Instance());
        isDigit->PushParameterType(&Instance());
        PushFunction(isPunctuation);

        const auto toUpper = new BuiltInMethod("ToUpper()", Describer::PublicStatic, &Instance());
        isDigit->PushParameterType(&Instance());
        PushFunction(toUpper);

        const auto toLower = new BuiltInMethod("ToLower()", Describer::PublicStatic, &Instance());
        isDigit->PushParameterType(&Instance());
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

        const auto explicitFloat = new BuiltInCast(&Float::Instance(), "conv.r4");
        explicitFloat->PushParameterType(&Instance());
        PushExplicitCast(explicitFloat);

        const auto explicitDouble = new BuiltInCast(&Double::Instance(), "conv.r8");
        explicitDouble->PushParameterType(&Instance());
        PushExplicitCast(explicitDouble);

        const auto explicitString = new BuiltInCast(&String::Instance(), "callvirt instance string [mscorlib]System.Object::ToString()");
        explicitString->PushParameterType(&Instance());
        PushExplicitCast(explicitString);
    }
}

