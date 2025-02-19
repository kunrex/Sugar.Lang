#include "short.h"

#include "../../Nodes/Global/BuiltIn/built_in_cast.h"
#include "../../Nodes/Global/BuiltIn/built_in_method.h"
#include "../../Nodes/Global/BuiltIn/built_in_property.h"

#include "integer.h"
#include "long.h"
#include "./float.h"
#include "double.h"
#include "../Reference/string.h"
#include "../Generic/referenced.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_float = "[System.Runtime]System.Long";

namespace Analysis::Structure::Wrappers
{
    Short::Short() : Struct(cil_float, Describer::Public), SingletonService()
    { }

    void Short::InitialiseMembers()
    {
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Max", &Instance(), true, "ldc.i2 32767", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Min", &Instance(), true, "ldc.i2 -32767", false, ""));

        const auto tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, &Instance());
        tryParse->PushParameterType(&String::Instance());
        tryParse->PushParameterType(Referenced::Instance(&Instance()));
        PushFunction(tryParse);

        const auto implicitInteger = new BuiltInCast(&Integer::Instance(), "conv.i4");
        implicitInteger->PushParameterType(&Instance());
        PushImplicitCast(implicitInteger);

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
