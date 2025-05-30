#include "./string.h"

#include "../../Compilation/compilation_result.h"
#include "../../DataTypes/data_type_extensions.h"

#include "../Value/integer.h"
#include "../Value/boolean.h"
#include "../Value/character.h"
#include "../Generic/array.h"

#include "../Value/built_in_functions.h"

#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_indexer.h"
#include "../../Global/BuiltIn/built_in_operation.h"
#include "../../Global/BuiltIn/built_in_property.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_string = "[System.Runtime]System.String";

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

    String::String() : BuiltInClass(cil_string, Describer::Public), SingletonService(), characteristics(), functions(), indexer(nullptr), overloads()
    {
        BindGlobal();
    }

    const String* String::Instance()
    {
        static const String instance;
        return &instance;
    }

    TypeKind String::Type() const { return TypeKind::String; }

    void String::BindGlobal()
    {
        characteristics.push_back(new BuiltInProperty("Length", Describer::Public, Integer::Instance(), true, "callvirt instance int32 class [System.Runtime]System.String::get_Length()", false, ""));
        characteristics.push_back(new BuiltInProperty("Empty", Describer::PublicStatic | Describer::Const, this, true, "ldsfld string [System.Runtime]System.String::Empty", false, ""));

        const auto clone = new BuiltInMethod("Clone", Describer::Public, this, "call instance string class [System.Runtime]System.String::Clone()");
        functions.emplace_back(std::hash<string>()("Clone") ^ ArgumentHash(clone), clone);

        const auto contains = new BuiltInMethod("Contains", Describer::Public, Boolean::Instance(), "instance bool class [System.Runtime]System.String::Contains(string)");
        contains->PushParameterType(this);
        functions.emplace_back(std::hash<string>()("Contains") ^ ArgumentHash(contains), contains);

        const auto containsCharacter = new BuiltInMethod("Contains", Describer::Public, Boolean::Instance(), "instance bool class [System.Runtime]System.String::Contains(char)");
        containsCharacter->PushParameterType(Character::Instance());
        functions.emplace_back(std::hash<string>()("Contains") ^ ArgumentHash(containsCharacter), containsCharacter);

        const auto toUpper = new BuiltInMethod("ToUpper", Describer::Public, this, "instance string class [System.Runtime]System.String::ToUpper()");
        functions.emplace_back(std::hash<string>()("ToUpper") ^ ArgumentHash(toUpper), toUpper);

        const auto toLower = new BuiltInMethod("ToLower", Describer::Public, this, "instance string class [System.Runtime]System.String::ToLower()");
        functions.emplace_back(std::hash<string>()("ToLower") ^ ArgumentHash(toLower), toLower);

        const auto trim = new BuiltInMethod("Trim", Describer::Public, this, "instance string class [System.Runtime]System.String::Trim()");
        functions.emplace_back(std::hash<string>()("Trim") ^ ArgumentHash(trim), trim);

        const auto trimStart = new BuiltInMethod("TrimStart", Describer::Public, this, "instance string class [System.Runtime]System.String::TrimStart()");
        functions.emplace_back(std::hash<string>()("TrimStart") ^ ArgumentHash(trimStart), trimStart);

        const auto trimEnd = new BuiltInMethod("TrimEnd", Describer::Public, this, "instance string class [System.Runtime]System.String::TrimEnd()");
        functions.emplace_back(std::hash<string>()("TrimEnd") ^ ArgumentHash(trimEnd), trimEnd);

        const auto substring = new BuiltInMethod("Substring", Describer::Public, this, "instance string class [System.Runtime]System.String::Substring(int)");
        substring->PushParameterType(Integer::Instance());
        functions.emplace_back(std::hash<string>()("Subtring") ^ ArgumentHash(substring), substring);

        const auto substringLength = new BuiltInMethod("Substring", Describer::Public, this, "instance string class [System.Runtime]System.String::Substring(int, int)");
        substringLength->PushParameterType(Integer::Instance());
        substringLength->PushParameterType(Integer::Instance());
        functions.emplace_back(std::hash<string>()("Subtring") ^ ArgumentHash(substringLength), substringLength);

        const auto startsWith = new BuiltInMethod("StartsWith", Describer::Public, Boolean::Instance(), "instance bool class [System.Runtime]System.String::StartsWith(string)");
        startsWith->PushParameterType(this);
        functions.emplace_back(std::hash<string>()("StartsWith") ^ ArgumentHash(startsWith), startsWith);

        const auto startsWithCharacter = new BuiltInMethod("StartsWith", Describer::Public, Boolean::Instance(), "instance bool class [System.Runtime]System.String::StartsWith(char)");
        startsWithCharacter->PushParameterType(Character::Instance());
        functions.emplace_back(std::hash<string>()("StartsWith") ^ ArgumentHash(startsWithCharacter), startsWithCharacter);

        const auto endsWith = new BuiltInMethod("EndsWith", Describer::Public, Boolean::Instance(), "instance bool class [System.Runtime]System.String::EndsWith(string)");
        endsWith->PushParameterType(this);
        functions.emplace_back(std::hash<string>()("EndsWith") ^ ArgumentHash(endsWith), endsWith);

        const auto endsWithCharacter = new BuiltInMethod("EndsWith", Describer::Public, Boolean::Instance(), "instance bool class [System.Runtime]System.String::EndsWith(char)");
        endsWithCharacter->PushParameterType(this);
        functions.emplace_back(std::hash<string>()("EndsWith") ^ ArgumentHash(endsWithCharacter), endsWithCharacter);

        const auto toCharArray = new BuiltInMethod("ToCharArray", Describer::Public, Array::Instance(Character::Instance()), "instance char[] class [System.Runtime]System.String::ToCharArray()");
        functions.emplace_back(std::hash<string>()("ToCharArray") ^ ArgumentHash(toCharArray), toCharArray);

        const auto split = new BuiltInMethod("Split", Describer::Public, Array::Instance(this), "instance string[] class [System.Runtime]System.String::Split(char[])");
        split->PushParameterType(Array::Instance(Character::Instance()));
        functions.emplace_back(std::hash<string>()("Split") ^ ArgumentHash(split), split);

        indexer = new BuiltInIndexer(Character::Instance(), true, "instance char class [System.Runtime]System.String::get_Chars(int32)", false, "");
        indexer->PushParameterType(Integer::Instance());

        const auto concatenation = new BuiltInOperation(SyntaxKind::Addition, this, "call string class [System.Runtime]System.String::Concat(string, string)", Concatenation);
        concatenation->PushParameterType(this);
        concatenation->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Addition, concatenation);

        const auto multiplication = new BuiltInOperation(SyntaxKind::Multiplication, this, "call class [System.Linq]System.Collections.Generic.IEnumerable`1<string> [System.Linq]System.Linq.Enumerable::Repeat<string>(!!0, int32) call string [System.Runtime]System.String::Concat(class [System.Runtime]System.Collections.Generic.IEnumerable`1<string>)", StringMultiply);
        multiplication->PushParameterType(this);
        multiplication->PushParameterType(Integer::Instance());
        overloads.emplace_back(SyntaxKind::Multiplication, multiplication);

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, Boolean::Instance(), "[System.Runtime]System.String::Equals(string, string)", Equals<string>);
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Equals, equals);

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, Boolean::Instance(), "[System.Runtime]System.String::Equals(string, string) ldc.i4.0 ceq", NotEquals<string>);
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::NotEquals, notEquals);
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
            if (std::get<0>(function) == hash)
                return std::get<1>(function);

        return nullptr;
    }

    const IConstructor* String::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* String::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        return ArgumentHash(argumentList) == ArgumentHash(indexer) ? indexer : nullptr;
    }

    const IFunction* String::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

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
        for (const auto cast: overloads)
            if (std::get<0>(cast) == base)
                return std::get<1>(cast);

        return nullptr;
    }

    String::~String()
    {
        for (const auto characteristic: characteristics)
            delete characteristic;

        for (const auto function: functions)
            delete std::get<1>(function);

        delete indexer;

        for (const auto overload: overloads)
            delete std::get<1>(overload);
    }
}
