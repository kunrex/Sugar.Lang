#include "./string.h"

#include "../../Nodes/Global/BuiltIn/built_in_method.h"
#include "../../Nodes/Global/BuiltIn/built_in_indexer.h"
#include "../../Nodes/Global/BuiltIn/built_in_property.h"

#include "../Value/boolean.h"
#include "../Value/character.h"
#include "../Value/integer.h"
#include "../Generic/array.h"

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_string = "[System.Runtime]System.String";

namespace Analysis::Structure::Wrappers
{
    String::String() : Class(cil_string, Describer::Public), SingletonService()
    { }

    void String::InitialiseMembers()
    {
        PushCharacteristic(new BuiltInProperty(Describer::Public, "Length", &Integer::Instance(), true, "callvirt instance int32 [System.Runtime]System.String::get_Length()", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Empty", &Instance(), true, "ldsfld string [System.Runtime]System.String::Empty", false, ""));

        const auto clone = new BuiltInMethod("Clone", Describer::Public, &Instance());
        clone->PushParameterType(&Instance());
        PushFunction(clone);

        const auto contains = new BuiltInMethod("Contains", Describer::Public, &Boolean::Instance());
        contains->PushParameterType(&Instance());
        PushFunction(contains);

        const auto containsCharacter = new BuiltInMethod("Contains", Describer::Public, &Boolean::Instance());
        contains->PushParameterType(&Character::Instance());
        PushFunction(containsCharacter);

        const auto toUpper = new BuiltInMethod("ToUpper", Describer::Public, &Instance());
        PushFunction(toUpper);

        const auto toLower = new BuiltInMethod("ToLower", Describer::Public, &Instance());
        PushFunction(toLower);

        const auto trim = new BuiltInMethod("Trim", Describer::Public, &Instance());
        PushFunction(trim);

        const auto trimStart = new BuiltInMethod("TrimStart", Describer::Public, &Instance());
        PushFunction(trimStart);

        const auto trimEnd = new BuiltInMethod("TrimEnd", Describer::Public, &Instance());
        PushFunction(trimEnd);

        const auto substring = new BuiltInMethod("Substring", Describer::Public, &Instance());
        substring->PushParameterType(&Integer::Instance());
        substring->PushParameterType(&Integer::Instance());
        PushFunction(substring);

        const auto startsWith = new BuiltInMethod("StartsWith", Describer::Public, &Boolean::Instance());
        startsWith->PushParameterType(&Instance());
        PushFunction(startsWith);

        const auto startsWithCharacter = new BuiltInMethod("StartsWith", Describer::Public, &Boolean::Instance());
        startsWithCharacter->PushParameterType(&Character::Instance());
        PushFunction(startsWithCharacter);

        const auto endsWith = new BuiltInMethod("EndsWith", Describer::Public, &Boolean::Instance());
        endsWith->PushParameterType(&Instance());
        PushFunction(endsWith);

        const auto endsWithCharacter = new BuiltInMethod("EndsWith", Describer::Public, &Boolean::Instance());
        endsWithCharacter->PushParameterType(&Character::Instance());
        PushFunction(endsWithCharacter);

        const auto toCharArray = new BuiltInMethod("ToCharArray", Describer::Public, Array::Instance(&Character::Instance()));
        PushFunction(toCharArray);

        const auto split = new BuiltInMethod("Split", Describer::Public, Array::Instance(&Instance()));
        split->PushParameterType(Array::Instance(&Character::Instance()));
        PushFunction(split);

        const auto indexer = new BuiltInIndexer(&Character::Instance(), true, "callvirt instance char System.String::get_Chars(int32)", false, "");
        PushIndexer(indexer);
    }
}
