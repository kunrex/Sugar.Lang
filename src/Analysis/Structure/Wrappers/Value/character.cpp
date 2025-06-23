#include "character.h"

#include "short.h"
#include "integer.h"
#include "long.h"
#include "boolean.h"
#include "built_in_functions.h"

#include "../Reference/string.h"

#include "../../Compilation/compilation_result.h"

#include "../../DataTypes/data_type_extensions.h"

#include "../../Global/Properties/property.h"
#include "../../Global/Functions/cast_overload.h"
#include "../../Global/Functions/method_function.h"
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
    Character::Character() : BuiltInValueType("char", Describer::Public), SingletonService(), characteristics()
    { }

    Character Character::instance;

    const Character* Character::Instance() { return &instance; }

    void Character::BindGlobalInstance()
    {
        static bool bound;

        if (!bound)
        {
            instance.BindGlobal();
            bound = true;
        }
    }

    int Character::SlotCount() const { return 1; }

    TypeKind Character::Type() const { return TypeKind::Character; }

    void Character::BindGlobal()
    {
        characteristics[0] = new BuiltInProperty("MinValue", Describer::PublicStatic, this, true, "ldsfld char System.Char::MinValue", false, "");
        characteristics[1] = new BuiltInProperty("MaxValue", Describer::PublicStatic, this, true, "ldsfld char System.Char::MaxValue", false, "");

        const auto isDigit = new BuiltInMethod("IsDigit", Describer::PublicStatic, Boolean::Instance(), "call bool [System.Runtime]System.Char::IsDigit(char)");
        isDigit->PushParameterType(this);
        functions[0] = { std::hash<string>()(isDigit->Name()) ^ ArgumentHash(isDigit), isDigit };

        const auto isLetter = new BuiltInMethod("IsLetter", Describer::PublicStatic, Boolean::Instance(), "call bool [System.Runtime]System.Char::IsLetter(char)");
        isLetter->PushParameterType(this);
        functions[1] = { std::hash<string>()(isLetter->Name()) ^ ArgumentHash(isLetter), isLetter };

        const auto isDigitOrLetter = new BuiltInMethod("IsLetterOrDigit", Describer::PublicStatic, Boolean::Instance(), "call bool [System.Runtime]System.Char::IsLetterOrDigit(char)");
        isDigitOrLetter->PushParameterType(this);
        functions[2] = { std::hash<string>()(isDigitOrLetter->Name()) ^ ArgumentHash(isDigitOrLetter), isDigitOrLetter };

        const auto isWhiteSpace = new BuiltInMethod("IsWhiteSpace", Describer::PublicStatic, Boolean::Instance(), "call bool [System.Runtime]System.Char::IsWhiteSpace(char)");
        isWhiteSpace->PushParameterType(this);
        functions[3] = { std::hash<string>()(isWhiteSpace->Name()) ^ ArgumentHash(isWhiteSpace), isWhiteSpace };

        const auto isPunctuation = new BuiltInMethod("IsPunctuation", Describer::PublicStatic, Boolean::Instance(), "call bool [System.Runtime]System.Char::IsPunctuation(char)");
        isPunctuation->PushParameterType(this);
        functions[4] = { std::hash<string>()(isPunctuation->Name()) ^ ArgumentHash(isPunctuation), isPunctuation };

        const auto toUpper = new BuiltInMethod("ToUpper()", Describer::Public, this, "callvirt instance char [System.Runtime]System.Char::ToUpper()");
        functions[5] = { std::hash<string>()(toUpper->Name()) ^ ArgumentHash(toUpper), toUpper };

        const auto toLower = new BuiltInMethod("ToLower()", Describer::Public, this, "callvirt instance char [System.Runtime]System.Char::ToLower()");
        functions[6] = { std::hash<string>()(toLower->Name()) ^ ArgumentHash(toLower), toLower };

        const auto getHash = GetHash();
        functions[7] = { std::hash<string>()(getHash->Name()) ^ ArgumentHash(getHash), getHash };

        const auto implicitInteger = new BuiltInCast(Integer::Instance(), "conv.i4", IntCast<char>);
        implicitInteger->PushParameterType(this);
        implicitCasts[0] = { ArgumentHash({ Integer::Instance(), this }), implicitInteger };
        explicitCasts[0] = { ArgumentHash({ Integer::Instance(), this }), new BuiltInCast(*implicitInteger) };

        const auto explicitShort = new BuiltInCast(Short::Instance(), "conv.i2", ShortCast<char>);
        explicitShort->PushParameterType(this);
        explicitCasts[1] = { ArgumentHash({ Short::Instance(), this }), explicitShort };

        const auto explicitLong = new BuiltInCast(Long::Instance(), "conv.i8", LongCast<char>);
        explicitLong->PushParameterType(this);
        explicitCasts[2] = { ArgumentHash({ Long::Instance(), this }), explicitLong };

        const auto implicitString = new BuiltInCast(String::Instance(), "call instance string [System.Runtime]System.Char::ToString()", StringCast<char>);
        implicitString->PushParameterType(this);
        implicitCasts[1] =  { ArgumentHash({ String::Instance(), this }), implicitString };
        explicitCasts[3] = { ArgumentHash({ String::Instance(), this }), new BuiltInCast(*implicitString) };

        const auto equals = new BuiltInOverload(SyntaxKind::Equals, this, "ceq", Equals<char>);
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads[0] = { SyntaxKind::Equals, equals };

        const auto notEquals = new BuiltInOverload(SyntaxKind::NotEquals, this, "ceq ldc.i4.0 ceq", NotEquals<char>);
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads[1] = { SyntaxKind::NotEquals, notEquals };
    }

    const ICharacteristic* Character::FindCharacteristic(const string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    const IFunctionDefinition* Character::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) & ArgumentHash(argumentList);

        for (const auto function: functions)
            if (function.first == hash)
                return function.second;

        return nullptr;
    }

    const IConstructor* Character::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Character::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Character::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });

        for (const auto cast: implicitCasts)
            if (cast.first == hash)
                return cast.second;

        return nullptr;
    }

    const IFunction* Character::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
       return FindBuiltInCast(returnType, fromType);
    }

    const IBuiltInCast* Character::FindBuiltInCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });

        for (const auto cast: explicitCasts)
            if (cast.first == hash)
                return cast.second;

        return nullptr;
    }

    const IOperatorOverload* Character::FindOverload(const SyntaxKind base) const
    {
        return FindBuiltInOverload(base);
    }

    const IBuiltInOverload* Character::FindBuiltInOverload(const SyntaxKind base) const
    {
        for (const auto overload: overloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    Character::~Character()
    {
        for (const auto characteristic : characteristics)
            delete characteristic;

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

