#include "integer.h"

#include "../../Nodes/Global/BuiltIn/built_in_cast.h"
#include "../../Nodes/Global/BuiltIn/built_in_method.h"
#include "../../Nodes/Global/BuiltIn/built_in_property.h"

#include "short.h"
#include "long.h"
#include "./float.h"
#include "double.h"
#include "../Reference/string.h"
#include "../Generic/referenced.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_float = "[System.Runtime]System.Integer";

namespace Analysis::Structure::Wrappers
{
    Integer::Integer() : Struct(cil_float, Describer::Public), SingletonService()
    { }

    void Integer::InitialiseMembers()
    {
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Max", &Instance(), true, "ldc.i4 2147483647", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Min", &Instance(), true, "ldc.i4 -2147483647", false, ""));

        const auto tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, &Instance());
        tryParse->PushParameterType(&String::Instance());
        tryParse->PushParameterType(Referenced::Instance(&Instance()));
        PushFunction(tryParse);

        const auto explicitShort = new BuiltInCast(&Short::Instance(), "conv.i2");
        explicitShort->PushParameterType(&Instance());
        PushExplicitCast(explicitShort);

        const auto implicitLong = new BuiltInCast(&Long::Instance(), "conv.i8");
        implicitLong->PushParameterType(&Instance());
        PushImplicitCast(implicitLong);

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


