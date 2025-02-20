#include "./string.h"

#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_indexer.h"
#include "../../Global/BuiltIn/built_in_property.h"

#include "../Value/integer.h"
#include "../Value/boolean.h"
#include "../Value/character.h"
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
        PushCharacteristic(new BuiltInProperty(Describer::Public, "Length", &Integer::Instance(), true, "callvirt instance int32 class [System.Runtime]System.String::get_Length()", false, ""));
        PushCharacteristic(new BuiltInProperty(Describer::PublicStatic, "Empty", &Instance(), true, "ldsfld string [System.Runtime]System.String::Empty", false, ""));

        const auto clone = new BuiltInMethod("Clone", Describer::Public, &Instance(), "call instance string class [System.Runtime]System.String::Clone()");
        PushFunction(clone);

        const auto contains = new BuiltInMethod("Contains", Describer::Public, &Boolean::Instance(), "instance bool class [System.Runtime]System.String::Contains(string)");
        contains->PushParameterType(&Instance());
        PushFunction(contains);

        const auto containsCharacter = new BuiltInMethod("Contains", Describer::Public, &Boolean::Instance(), "instance bool class [System.Runtime]System.String::Contains(char)");
        contains->PushParameterType(&Character::Instance());
        PushFunction(containsCharacter);

        const auto toUpper = new BuiltInMethod("ToUpper", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::ToUpper()");
        PushFunction(toUpper);

        const auto toLower = new BuiltInMethod("ToLower", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::ToLower()");
        PushFunction(toLower);

        const auto trim = new BuiltInMethod("Trim", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::Trim()");
        PushFunction(trim);

        const auto trimStart = new BuiltInMethod("TrimStart", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::TrimStart()");
        PushFunction(trimStart);

        const auto trimEnd = new BuiltInMethod("TrimEnd", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::TrimEnd()");
        PushFunction(trimEnd);

        const auto substring = new BuiltInMethod("Substring", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::Substring(int)");
        substring->PushParameterType(&Integer::Instance());
        PushFunction(substring);

        const auto substringLength = new BuiltInMethod("Substring", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::Substring(int, int)");
        substringLength->PushParameterType(&Integer::Instance());
        substringLength->PushParameterType(&Integer::Instance());
        PushFunction(substringLength);

        const auto startsWith = new BuiltInMethod("StartsWith", Describer::Public, &Boolean::Instance(), "instance bool class [System.Runtime]System.String::StartsWith(string)");
        startsWith->PushParameterType(&Instance());
        PushFunction(startsWith);

        const auto startsWithCharacter = new BuiltInMethod("StartsWith", Describer::Public, &Boolean::Instance(), "instance bool class [System.Runtime]System.String::StartsWith(char)");
        startsWithCharacter->PushParameterType(&Character::Instance());
        PushFunction(startsWithCharacter);

        const auto endsWith = new BuiltInMethod("EndsWith", Describer::Public, &Boolean::Instance(), "instance bool class [System.Runtime]System.String::EndsWith(string)");
        endsWith->PushParameterType(&Instance());
        PushFunction(endsWith);

        const auto endsWithCharacter = new BuiltInMethod("EndsWith", Describer::Public, &Boolean::Instance(), "instance bool class [System.Runtime]System.String::EndsWith(char)");
        endsWithCharacter->PushParameterType(&Character::Instance());
        PushFunction(endsWithCharacter);

        const auto toCharArray = new BuiltInMethod("ToCharArray", Describer::Public, Array::Instance(&Character::Instance()), "instance char[] class [System.Runtime]System.String::ToCharArray()");
        PushFunction(toCharArray);

        const auto split = new BuiltInMethod("Split", Describer::Public, Array::Instance(&Instance()), "instance string[] class [System.Runtime]System.String::Split(char[])");
        split->PushParameterType(Array::Instance(&Character::Instance()));
        PushFunction(split);

        const auto indexer = new BuiltInIndexer(&Character::Instance(), true, "instance char class [System.Runtime]System.String::get_Chars(int32)", false, "");
        indexer->PushParameterType(&Integer::Instance());
        PushIndexer(indexer);
    }
}
