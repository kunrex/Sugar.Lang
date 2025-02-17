#include "./string.h"

#include "../../Nodes/Global/BuiltIn/built_in_property.h"

using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Wrappers
{
    String::String() : Class("string", Describer::Public)
    {

    }

    void String::InitialiseMembers()
    {
        const auto length = new Global::BuiltInProperty(Describer::Public, "Length", Integer::Instance(), "callvirt instance int32 [mscorlib]System.String::get_Length()", nullptr);
    }
}
