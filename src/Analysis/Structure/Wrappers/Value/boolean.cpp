#include "boolean.h"

#include "long.h"
#include "integer.h"
#include "short.h"
#include "../Reference/string.h"

#include "../../Global/BuiltIn/built_in_cast.h"

using namespace Analysis::Structure::Global;

constexpr std::string cil_character = "[System.Runtime]System.Boolean";

namespace Analysis::Structure::Wrappers
{
    Boolean::Boolean() : Struct(cil_character, Enums::Describer::Public), SingletonService()
    { }

    int Boolean::SlotCount() const { return 1; }

    void Boolean::InitialiseMembers()
    {
        const auto implicitShort = new BuiltInCast(&Short::Instance(), "conv.i2");
        implicitShort->PushParameterType(&Instance());
        PushExplicitCast(implicitShort);

        const auto implicitInteger = new BuiltInCast(&Integer::Instance(), "conv.i4");
        implicitInteger->PushParameterType(&Instance());
        PushExplicitCast(implicitInteger);

        const auto implicitLong = new BuiltInCast(&Long::Instance(), "conv.i8");
        implicitLong->PushParameterType(&Instance());
        PushExplicitCast(implicitLong);

        const auto explicitString = new BuiltInCast(&String::Instance(), "callvirt instance string [mscorlib]System.Object::ToString()");
        explicitString->PushParameterType(&Instance());
        PushExplicitCast(explicitString);
    }
}
