#include "double.h"

#include "../../Nodes/Global/BuiltIn/built_in_cast.h"
#include "../../Nodes/Global/BuiltIn/built_in_method.h"
#include "../../Nodes/Global/BuiltIn/built_in_property.h"

#include "short.h"
#include "integer.h"
#include "long.h"
#include "./float.h"
#include "../Reference/string.h"
#include "../Generic/referenced.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_float = "[System.Runtime]System.Double";

namespace Analysis::Structure::Wrappers
{
    Double::Double() : Struct(cil_float, Describer::Public), SingletonService()
    { }

    void Double::InitialiseMembers()
    {
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Max", &Instance(), true, "ldc.r8 1.7976931348623157E+308", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Min", &Instance(), true, "ldc.r8 -1.7976931348623157E+308", false, ""));

        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "NaN", &Instance(), true, "ldc.r8 NaN", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "PositiveInfinity", &Instance(), true, "ldc.r8 Infinity", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "NegativeInfinity", &Instance(), true, "ldc.r8 -Infinity", false, ""));

        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Epsilon", &Instance(), true, "ldc.r8 4.94065645841247E-324", false, ""));

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

        const auto explicitFloat = new BuiltInCast(&Float::Instance(), "conv.r4");
        explicitFloat->PushParameterType(&Instance());
        PushExplicitCast(explicitFloat);

        const auto explicitString = new BuiltInCast(&String::Instance(), "callvirt instance string [mscorlib]System.Object::ToString()");
        explicitString->PushParameterType(&Instance());
        PushExplicitCast(explicitString);
    }
}
