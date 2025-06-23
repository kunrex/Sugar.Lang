#include "./string.h"

#include "object.h"
#include "../Value/integer.h"
#include "../Value/boolean.h"
#include "../Value/character.h"
#include "../Generic/array.h"
#include "../Value/built_in_functions.h"

#include "../../Compilation/compilation_result.h"
#include "../../DataTypes/data_type_extensions.h"
#include "../../Global/Functions/cast_overload.h"
#include "../../Global/Functions/method_function.h"

#include "../../Global/Properties/indexer.h"
#include "../../Global/Properties/property.h"
#include "../../Global/Functions/operator_overload.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Wrappers
{
    CompilationResult Concatenation(const std::vector<CompilationResult>& arguments)
    {
        string result;
        for (const auto& argument: arguments)
            result += std::get<string>(argument.data);

        return { String::Instance(), result };
    }

    CompilationResult StringMultiply(const std::vector<CompilationResult>& arguments)
    {
        string result;
        const auto lhs = std::get<string>(arguments[0].data);
        const auto rhs = std::get<int>(arguments[1].data);
        for (auto i = 0; i < rhs; i++)
            result += lhs;

        return { String::Instance(), result };
    }

    String::String() : BuiltInClass("string", Describer::Public), SingletonService(), characteristics(), indexer(nullptr), implicitObject(nullptr)
    { }

    String String::instance;

    const String* String::Instance() { return &instance; }

    void String::BindGlobalInstance()
    {
        static bool bound;

        if (!bound)
        {
            instance.BindGlobal();
            bound = true;
        }
    }

    TypeKind String::Type() const { return TypeKind::String; }

    void String::BindGlobal()
    {
        characteristics[0] = new BuiltInProperty("Length", Describer::Public, Integer::Instance(), true, "callvirt instance int32 class [System.Runtime]System.String::get_Length()", false, "");
        characteristics[1] = new BuiltInProperty("Empty", Describer::PublicStatic | Describer::Const, this, true, "ldsfld string [System.Runtime]System.String::Empty", false, "");

        const auto clone = new BuiltInMethod("Clone", Describer::Public, this, "call instance string class [System.Runtime]System.String::Clone()");
        functions[0] = { std::hash<string>()(clone->Name()) ^ ArgumentHash(clone), clone };

        const auto contains = new BuiltInMethod("Contains", Describer::Public, Boolean::Instance(), "callvirt instance bool [System.Runtime]System.String::Contains(string)");
        contains->PushParameterType(this);
        functions[1] = { std::hash<string>()(contains->Name()) ^ ArgumentHash(contains), contains };

        const auto containsCharacter = new BuiltInMethod("Contains", Describer::Public, Boolean::Instance(), "callvirt instance bool [System.Runtime]System.String::Contains(char)");
        containsCharacter->PushParameterType(Character::Instance());
        functions[2] = { std::hash<string>()(containsCharacter->Name()) ^ ArgumentHash(containsCharacter), containsCharacter };

        const auto toUpper = new BuiltInMethod("ToUpper", Describer::Public, this, "callvirt instance string [System.Runtime]System.String::ToUpper()");
        functions[3] = { std::hash<string>()(toUpper->Name()) ^ ArgumentHash(toUpper), toUpper };

        const auto toLower = new BuiltInMethod("ToLower", Describer::Public, this, "callvirt instance string [System.Runtime]System.String::ToLower()");
        functions[4] = { std::hash<string>()(toLower->Name()) ^ ArgumentHash(toLower), toLower };

        const auto trim = new BuiltInMethod("Trim", Describer::Public, this, "callvirt instance string [System.Runtime]System.String::Trim()");
        functions[5] = { std::hash<string>()(trim->Name()) ^ ArgumentHash(trim), trim };

        const auto trimStart = new BuiltInMethod("TrimStart", Describer::Public, this, "callvirt instance string [System.Runtime]System.String::TrimStart()");
        functions[6] = { std::hash<string>()(trimStart->Name()) ^ ArgumentHash(trimStart), trimStart };

        const auto trimEnd = new BuiltInMethod("TrimEnd", Describer::Public, this, "callvirt instance string [System.Runtime]System.String::TrimEnd()");
        functions[7] = { std::hash<string>()(trimEnd->Name()) ^ ArgumentHash(trimEnd), trimEnd };

        const auto substring = new BuiltInMethod("Substring", Describer::Public, this, "callvirt instance string [System.Runtime]System.String::Substring(int)");
        substring->PushParameterType(Integer::Instance());
        functions[8] = { std::hash<string>()(substring->Name()) ^ ArgumentHash(substring), substring };

        const auto substringLength = new BuiltInMethod("Substring", Describer::Public, this, "callvirt instance string class [System.Runtime]System.String::Substring(int, int)");
        substringLength->PushParameterType(Integer::Instance());
        substringLength->PushParameterType(Integer::Instance());
        functions[9] = { std::hash<string>()(substringLength->Name()) ^ ArgumentHash(substringLength), substringLength };

        const auto startsWith = new BuiltInMethod("StartsWith", Describer::Public, Boolean::Instance(), "callvirt instance bool [System.Runtime]System.String::StartsWith(string)");
        startsWith->PushParameterType(this);
        functions[10] = { std::hash<string>()(startsWith->Name()) ^ ArgumentHash(startsWith), startsWith };

        const auto startsWithCharacter = new BuiltInMethod("StartsWith", Describer::Public, Boolean::Instance(), "callvirt instance bool [System.Runtime]System.String::StartsWith(char)");
        startsWithCharacter->PushParameterType(Character::Instance());
        functions[11] = { std::hash<string>()(startsWithCharacter->Name()) ^ ArgumentHash(startsWithCharacter), startsWithCharacter };

        const auto endsWith = new BuiltInMethod("EndsWith", Describer::Public, Boolean::Instance(), "callvirt instance bool [System.Runtime]System.String::EndsWith(string)");
        endsWith->PushParameterType(this);
        functions[12] = { std::hash<string>()(endsWith->Name()) ^ ArgumentHash(endsWith), endsWith };

        const auto endsWithCharacter = new BuiltInMethod("EndsWith", Describer::Public, Boolean::Instance(), "callvirt instance bool [System.Runtime]System.String::EndsWith(char)");
        endsWithCharacter->PushParameterType(this);
        functions[13] = { std::hash<string>()(endsWithCharacter->Name()) ^ ArgumentHash(endsWithCharacter), endsWithCharacter };

        const auto toCharArray = new BuiltInMethod("ToCharArray", Describer::Public, Array::Instance(Character::Instance()), "callvirt instance char[] [System.Runtime]System.String::ToCharArray()");
        functions[14] = { std::hash<string>()(toCharArray->Name()) ^ ArgumentHash(toCharArray), toCharArray };

        const auto split = new BuiltInMethod("Split", Describer::Public, Array::Instance(this), "callvirt instance string[] [System.Runtime]System.String::Split(char[])");
        split->PushParameterType(Array::Instance(Character::Instance()));
        functions[15] = { std::hash<string>()(split->Name()) ^ ArgumentHash(split), split };

        const auto getHash = GetHash();
        functions[16] = { std::hash<string>()(getHash->Name()) ^ ArgumentHash(getHash), getHash };

        const auto indexer = new BuiltInIndexer(Character::Instance(), true, "call instance char [System.Runtime]System.String::get_Chars(int32)", false, "");
        indexer->PushParameterType(Integer::Instance());
        this->indexer = indexer;

        const auto concatenation = new BuiltInOverload(SyntaxKind::Addition, this, "call string [System.Runtime]System.String::Concat(string, string)", Concatenation);
        concatenation->PushParameterType(this);
        concatenation->PushParameterType(this);
        overloads[0] = { SyntaxKind::Addition, concatenation };

        const auto multiplication = new BuiltInOverload(SyntaxKind::Multiplication, this, "call class [System.Linq]System.Collections.Generic.IEnumerable`1<string> [System.Linq]System.Linq.Enumerable::Repeat<string>(!!0, int32) call string [System.Runtime]System.String::Concat(class [System.Runtime]System.Collections.Generic.IEnumerable`1<string>)", StringMultiply);
        multiplication->PushParameterType(this);
        multiplication->PushParameterType(Integer::Instance());
        overloads[1] = { SyntaxKind::Multiplication, multiplication };

        const auto equals = new BuiltInOverload(SyntaxKind::Equals, Boolean::Instance(), "call bool [System.Runtime]System.String::op_Equality(string, string)", Equals<string>);
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads[2] = { SyntaxKind::Equals, equals };

        const auto notEquals = new BuiltInOverload(SyntaxKind::NotEquals, Boolean::Instance(), "call bool [System.Runtime]System.String::op_Equality(string, string) ldc.i4.0 ceq", NotEquals<string>);
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads[3] = { SyntaxKind::NotEquals, notEquals };

        this->implicitObject = ImplicitObject();
    }

    const ICharacteristic* String::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    const IFunctionDefinition* String::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) & ArgumentHash(argumentList);

        for (const auto function: functions)
            if (function.first == hash)
                return function.second;

        return nullptr;
    }

    const IConstructor* String::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* String::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        if (argumentList.size() != 1)
            return nullptr;

        if (argumentList[0] != Integer::Instance())
            return nullptr;

        return indexer;
    }

    const IFunction* String::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        if (returnType == Object::Instance() && fromType == this)
            return implicitObject;

        return nullptr;
    }

    const IFunction* String::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IBuiltInCast* String::FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* String::FindOverload(const SyntaxKind base) const
    {
        return FindBuiltInOverload(base);
    }

    const IBuiltInOverload* String::FindBuiltInOverload(const SyntaxKind base) const
    {
        for (const auto overload: overloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    String::~String()
    {
        for (const auto characteristic: characteristics)
            delete characteristic;

        for (const auto function: functions)
            delete function.second;

        delete indexer;

        for (const auto overload: overloads)
            delete overload.second;

        delete implicitObject;
    }
}
