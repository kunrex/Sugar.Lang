#include "character.h"

#include "../../DataTypes/data_type_extensions.h"

#include "short.h"
#include "integer.h"
#include "long.h"
#include "boolean.h"
#include "built_in_functions.h"
#include "../Reference/string.h"

#include "../../Compilation/compilation_result.h"

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_operation.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_character = "[System.Runtime]System.Char";

namespace Analysis::Structure::Wrappers
{
    Character::Character() : BuiltInValueType(cil_character, Describer::Public), SingletonService(), characteristics(), functions(), implicitCasts(), explicitCasts(), overloads()
    { }

    int Character::SlotCount() const { return 1; }

    TypeKind Character::Type() const { return TypeKind::Character; }

    const Character& Character::Instance()
    {
        static const Character instance;
        return instance;
    }

    void Character::BindGlobal()
    {
        characteristics["MinValue"] = new BuiltInProperty("MinValue", Describer::PublicStatic, &Instance(), true, "ldsfld char System.Char::MinValue", false, "");
        characteristics["MaxValue"] = new BuiltInProperty("MaxValue", Describer::PublicStatic, &Instance(), true, "ldsfld char System.Char::MaxValue", false, "");

        const auto isDigit = new BuiltInMethod("IsDigit", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsDigit(char)");
        isDigit->PushParameterType(&Boolean::Instance());
        functions[std::hash<string>()("IsDigit") ^ ArgumentHash(isDigit)] = isDigit;

        const auto isLetter = new BuiltInMethod("IsLetter", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsLetter(char)");
        isDigit->PushParameterType(&Boolean::Instance());
        functions[std::hash<string>()("IsLetter") ^ ArgumentHash(isLetter)] = isLetter;

        const auto isDigitOrLetter = new BuiltInMethod("IsLetterOrDigit", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsLetterOrDigit(char)");
        isDigit->PushParameterType(&Boolean::Instance());
        functions[std::hash<string>()("IsLetterOrDigit") ^ ArgumentHash(isDigitOrLetter)] = isDigitOrLetter;

        const auto isWhiteSpace = new BuiltInMethod("IsWhiteSpace", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsWhiteSpace(char)");
        isDigit->PushParameterType(&Boolean::Instance());
        functions[std::hash<string>()("IsWhiteSpace") ^ ArgumentHash(isWhiteSpace)] = isWhiteSpace;

        const auto isPunctuation = new BuiltInMethod("IsPunctuation", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsPunctuation(char)");
        isDigit->PushParameterType(&Boolean::Instance());
        functions[std::hash<string>()("IsPunctuation") ^ ArgumentHash(isPunctuation)] = isPunctuation;

        const auto toUpper = new BuiltInMethod("ToUpper()", Describer::Public, &Instance(), "instance char valuetype [System.Runtime]System.Char::ToUpper()");
        functions[std::hash<string>()("ToUpper") ^ ArgumentHash(toUpper)] = toUpper;

        const auto toLower = new BuiltInMethod("ToLower()", Describer::Public, &Instance(), "instance char valuetype [System.Runtime]System.Char::ToLower()");
        functions[std::hash<string>()("ToLower") ^ ArgumentHash(toLower)] = toLower;

        const auto implicitInteger = new BuiltInCast(&Integer::Instance(), "conv.i4", IntCast<char>);
        implicitInteger->PushParameterType(&Instance());
        implicitCasts[ArgumentHash({ &Integer::Instance(), &Instance()})] = implicitInteger;
        explicitCasts[ArgumentHash({ &Integer::Instance(), &Instance()})] = implicitInteger;

        const auto explicitShort = new BuiltInCast(&Short::Instance(), "conv.i2", ShortCast<char>);
        explicitShort->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Short::Instance(), &Instance()})] = explicitShort;

        const auto explicitLong = new BuiltInCast(&Long::Instance(), "conv.i8", LongCast<char>);
        explicitLong->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Long::Instance(), &Instance()})] = explicitLong;

        const auto implicitString = new BuiltInCast(&String::Instance(), "call instance string valuetype [System.Runtime]System.Char::ToString()", StringCast<char>);
        implicitString->PushParameterType(&Instance());
        implicitCasts[ArgumentHash({ &String::Instance(), &Instance()})] = implicitString;
        explicitCasts[ArgumentHash({ &String::Instance(), &Instance()})] = implicitString;

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, &Instance(), "ceq", Equals<char>);
        equals->PushParameterType(&Instance());
        equals->PushParameterType(&Instance());
        overloads[SyntaxKind::Equals] = equals;

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, &Instance(), "ceq ldc.i4.0 ceq", NotEquals<char>);
        notEquals->PushParameterType(&Instance());
        notEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::NotEquals] = notEquals;
    }

    const ICharacteristic* Character::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? characteristics.at(name) : nullptr;
    }

    const IFunctionDefinition* Character::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) & ArgumentHash(argumentList);
        return functions.contains(hash) ? functions.at(hash) : nullptr;
    }

    const IFunction* Character::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Character::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Character::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });
        return implicitCasts.contains(hash) ? implicitCasts.at(hash) : nullptr;
    }

    const IFunction* Character::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
       return FindBuiltInCast(returnType, fromType);
    }

    const IBuiltInCast* Character::FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });
        return explicitCasts.contains(hash) ? explicitCasts.at(hash) : nullptr;
    }

    const IOperatorOverload* Character::FindOverload(const SyntaxKind base) const
    {
        return overloads.contains(base) ? overloads.at(base) : nullptr;
    }

    const IBuiltInOverload* Character::FindBuiltInOverload(const SyntaxKind base) const
    {
        return overloads.contains(base) ? overloads.at(base) : nullptr;
    }

    Character::~Character()
    {
        for (const auto function: functions)
            delete function.second;

        for (const auto cast: implicitCasts)
            delete cast.second;

        for (const auto cast: explicitCasts)
            delete cast.second;

        for (const auto overload: overloads)
            delete overload.second;
    }
}

