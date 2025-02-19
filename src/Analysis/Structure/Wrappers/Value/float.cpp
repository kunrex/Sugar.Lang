#include "./float.h"

#include "../../Nodes/Global/BuiltIn/built_in_cast.h"
#include "../../Nodes/Global/BuiltIn/built_in_method.h"
#include "../../Nodes/Global/BuiltIn/built_in_property.h"

#include "short.h"
#include "integer.h"
#include "long.h"
#include "double.h"
#include "../Reference/string.h"
#include "../Generic/referenced.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_float = "[System.Runtime]System.Single";

namespace Analysis::Structure::Wrappers
{
    Float::Float() : Struct(cil_float, Describer::Public), SingletonService()
    { }

    void Float::InitialiseMembers()
    {
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Max", &Instance(), true, "ldc.r4 3.4028235E+38", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Min", &Instance(), true, "ldc.r4 -3.4028235E+38", false, ""));

        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "NaN", &Instance(), true, "ldc.r4 NaN", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "PositiveInfinity", &Instance(), true, "ldc.r4 Infinity", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "NegativeInfinity", &Instance(), true, "ldc.r4 -Infinity", false, ""));

        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Epsilon", &Instance(), true, "ldc.r4 1.401298E-45", false, ""));

        const auto tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, &Instance());
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

        const auto explicitString = new BuiltInCast(&String::Instance(), "callvirt instance string [mscorlib]System.Object::ToString()");
        explicitString->PushParameterType(&Instance());
        PushExplicitCast(explicitString);
    }
}

