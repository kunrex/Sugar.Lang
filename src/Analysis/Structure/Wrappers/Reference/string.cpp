#include "./string.h"

#include "../../DataTypes/data_type_extensions.h"

#include "../Value/integer.h"
#include "../Value/boolean.h"
#include "../Value/character.h"
#include "../Generic/array.h"

#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_indexer.h"
#include "../../Global/BuiltIn/built_in_operation.h"
#include "../../Global/BuiltIn/built_in_property.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

constexpr std::string cil_string = "[System.Runtime]System.String";

namespace Analysis::Structure::Wrappers
{
    String::String() : BuiltInClass(cil_string, Describer::Public), SingletonService(), characteristics(), functions(), indexer(nullptr), overloads()
    { }

    TypeKind String::Type() const { return TypeKind::String; }

    void String::InitializeMembers()
    {
        characteristics["Length"] = new BuiltInProperty(Describer::Public, "Length", &Integer::Instance(), true, "callvirt instance int32 class [System.Runtime]System.String::get_Length()", false, "");
        characteristics["Empty"] = new BuiltInProperty(Describer::PublicStatic, "Empty", &Instance(), true, "ldsfld string [System.Runtime]System.String::Empty", false, "");

        const auto clone = new BuiltInMethod("Clone", Describer::Public, &Instance(), "call instance string class [System.Runtime]System.String::Clone()");
        functions[std::hash<string>()("Clone") ^ ArgumentHash(clone)] = clone;

        const auto contains = new BuiltInMethod("Contains", Describer::Public, &Boolean::Instance(), "instance bool class [System.Runtime]System.String::Contains(string)");
        contains->PushParameterType(&Instance());
        functions[std::hash<string>()("Contains") ^ ArgumentHash(contains)] = contains;

        const auto containsCharacter = new BuiltInMethod("Contains", Describer::Public, &Boolean::Instance(), "instance bool class [System.Runtime]System.String::Contains(char)");
        contains->PushParameterType(&Character::Instance());
        functions[std::hash<string>()("Contains") ^ ArgumentHash(containsCharacter)] = containsCharacter;

        const auto toUpper = new BuiltInMethod("ToUpper", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::ToUpper()");
        functions[std::hash<string>()("ToUpper") ^ ArgumentHash(toUpper)] = toUpper;

        const auto toLower = new BuiltInMethod("ToLower", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::ToLower()");
        functions[std::hash<string>()("ToLower") ^ ArgumentHash(toLower)] = toLower;

        const auto trim = new BuiltInMethod("Trim", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::Trim()");
        functions[std::hash<string>()("Trim") ^ ArgumentHash(trim)] = trim;

        const auto trimStart = new BuiltInMethod("TrimStart", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::TrimStart()");
        functions[std::hash<string>()("TrimStart") ^ ArgumentHash(trimStart)] = trimStart;

        const auto trimEnd = new BuiltInMethod("TrimEnd", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::TrimEnd()");
        functions[std::hash<string>()("TrimEnd") ^ ArgumentHash(trimEnd)] = trimEnd;

        const auto substring = new BuiltInMethod("Substring", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::Substring(int)");
        substring->PushParameterType(&Integer::Instance());
        functions[std::hash<string>()("Subtring") ^ ArgumentHash(substring)] = substring;

        const auto substringLength = new BuiltInMethod("Substring", Describer::Public, &Instance(), "instance string class [System.Runtime]System.String::Substring(int, int)");
        substringLength->PushParameterType(&Integer::Instance());
        substringLength->PushParameterType(&Integer::Instance());
        functions[std::hash<string>()("Subtring") ^ ArgumentHash(substringLength)] = substringLength;

        const auto startsWith = new BuiltInMethod("StartsWith", Describer::Public, &Boolean::Instance(), "instance bool class [System.Runtime]System.String::StartsWith(string)");
        startsWith->PushParameterType(&Instance());
        functions[std::hash<string>()("StartsWith") ^ ArgumentHash(startsWith)] = startsWith;

        const auto startsWithCharacter = new BuiltInMethod("StartsWith", Describer::Public, &Boolean::Instance(), "instance bool class [System.Runtime]System.String::StartsWith(char)");
        startsWithCharacter->PushParameterType(&Character::Instance());
        functions[std::hash<string>()("StartsWith") ^ ArgumentHash(startsWithCharacter)] = startsWithCharacter;

        const auto endsWith = new BuiltInMethod("EndsWith", Describer::Public, &Boolean::Instance(), "instance bool class [System.Runtime]System.String::EndsWith(string)");
        endsWith->PushParameterType(&Instance());
        functions[std::hash<string>()("EndsWith") ^ ArgumentHash(endsWith)] = endsWith;

        const auto endsWithCharacter = new BuiltInMethod("EndsWith", Describer::Public, &Boolean::Instance(), "instance bool class [System.Runtime]System.String::EndsWith(char)");
        endsWithCharacter->PushParameterType(&Character::Instance());
        functions[std::hash<string>()("EndsWith") ^ ArgumentHash(endsWithCharacter)] = endsWithCharacter;

        const auto toCharArray = new BuiltInMethod("ToCharArray", Describer::Public, Array::Instance(&Character::Instance()), "instance char[] class [System.Runtime]System.String::ToCharArray()");
        functions[std::hash<string>()("ToCharArray") ^ ArgumentHash(toCharArray)] = toCharArray;

        const auto split = new BuiltInMethod("Split", Describer::Public, Array::Instance(&Instance()), "instance string[] class [System.Runtime]System.String::Split(char[])");
        split->PushParameterType(Array::Instance(&Character::Instance()));
        functions[std::hash<string>()("Split") ^ ArgumentHash(split)] = split;

        indexer = new BuiltInIndexer(&Character::Instance(), true, "instance char class [System.Runtime]System.String::get_Chars(int32)", false, "");
        indexer->PushParameterType(&Integer::Instance());

        const auto concatenation = new BuiltInOperation(SyntaxKind::Addition, &Instance(), "call string class [System.Runtime]System.String::Concat(string, string)");
        concatenation->PushParameterType(&Instance());
        concatenation->PushParameterType(&Instance());
        overloads[SyntaxKind::Addition] = concatenation;

        const auto multiplication = new BuiltInOperation(SyntaxKind::Multiplication, &Instance(), "call class [System.Linq]System.Collections.Generic.IEnumerable`1<string> [System.Linq]System.Linq.Enumerable::Repeat<string>(!!0, int32) call string [System.Runtime]System.String::Concat(class [System.Runtime]System.Collections.Generic.IEnumerable`1<string>)");
        multiplication->PushParameterType(&Instance());
        multiplication->PushParameterType(&Integer::Instance());
        overloads[SyntaxKind::Multiplication] = multiplication;
    }

    const ICharacteristic* String::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? characteristics.at(name) : nullptr;
    }

    const IFunctionDefinition* String::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) & ArgumentHash(argumentList);
        return functions.contains(hash) ? nullptr : functions.at(hash);
    }

    const IFunction* String::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* String::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        if (ArgumentHash(argumentList) == ArgumentHash(indexer))
            return indexer;
    }

    const IFunction* String::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* String::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* String::FindOverload(const SyntaxKind base) const
    {
        return overloads.contains(base) ? overloads.at(base) : nullptr;
    }

    String::~String()
    {
        for (const auto characteristic: characteristics)
            delete characteristic.second;

        for (const auto function: functions)
            delete function.second;

        delete indexer;

        for (const auto overload: overloads)
            delete overload.second;
    }
}
