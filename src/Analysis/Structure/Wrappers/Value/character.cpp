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
    Character::Character() : BuiltInValueType(cil_character, Describer::Public), SingletonService(), functions(), implicitCasts(), explicitCasts(), overloads()
    { }

    int Character::SlotCount() const { return 1; }

    TypeKind Character::Type() const { return TypeKind::Character; }

    const Character* Character::Instance()
    {
        static const Character instance;
        return &instance;
    }

    void Character::BindGlobal()
    {
        characteristics.push_back(new BuiltInProperty("MinValue", Describer::PublicStatic, this, true, "ldsfld char System.Char::MinValue", false, ""));
        characteristics.push_back(new BuiltInProperty("MaxValue", Describer::PublicStatic, this, true, "ldsfld char System.Char::MaxValue", false, ""));

        const auto isDigit = new BuiltInMethod("IsDigit", Describer::PublicStatic, Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsDigit(char)");
        isDigit->PushParameterType(this);
        functions.emplace_back(std::hash<string>()("IsDigit") ^ ArgumentHash(isDigit), isDigit);

        const auto isLetter = new BuiltInMethod("IsLetter", Describer::PublicStatic, Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsLetter(char)");
        isLetter->PushParameterType(this);
        functions.emplace_back(std::hash<string>()("IsLetter") ^ ArgumentHash(isLetter), isLetter);

        const auto isDigitOrLetter = new BuiltInMethod("IsLetterOrDigit", Describer::PublicStatic, Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsLetterOrDigit(char)");
        isDigitOrLetter->PushParameterType(this);
        functions.emplace_back(std::hash<string>()("IsLetterOrDigit") ^ ArgumentHash(isDigitOrLetter), isDigitOrLetter);

        const auto isWhiteSpace = new BuiltInMethod("IsWhiteSpace", Describer::PublicStatic, Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsWhiteSpace(char)");
        isWhiteSpace->PushParameterType(this);
        functions.emplace_back(std::hash<string>()("IsWhiteSpace") ^ ArgumentHash(isWhiteSpace), isWhiteSpace);

        const auto isPunctuation = new BuiltInMethod("IsPunctuation", Describer::PublicStatic, Boolean::Instance(), "bool valuetype [System.Runtime]System.Char::IsPunctuation(char)");
        isPunctuation->PushParameterType(this);
        functions.emplace_back(std::hash<string>()("IsPunctuation") ^ ArgumentHash(isPunctuation), isPunctuation);

        const auto toUpper = new BuiltInMethod("ToUpper()", Describer::Public, this, "instance char valuetype [System.Runtime]System.Char::ToUpper()");
        functions.emplace_back(std::hash<string>()("ToUpper") ^ ArgumentHash(toUpper), toUpper);

        const auto toLower = new BuiltInMethod("ToLower()", Describer::Public, this, "instance char valuetype [System.Runtime]System.Char::ToLower()");
        functions.emplace_back(std::hash<string>()("ToLower") ^ ArgumentHash(toLower), toLower);

        const auto implicitInteger = new BuiltInCast(Integer::Instance(), "conv.i4", IntCast<char>);
        implicitInteger->PushParameterType(this);
        implicitCasts.emplace_back(ArgumentHash({ Integer::Instance(), this }), implicitInteger);
        explicitCasts.emplace_back(ArgumentHash({ Integer::Instance(), this }), implicitInteger);

        const auto explicitShort = new BuiltInCast(Short::Instance(), "conv.i2", ShortCast<char>);
        explicitShort->PushParameterType(Instance());
        explicitCasts.emplace_back(ArgumentHash({ Short::Instance(), this }), explicitShort);

        const auto explicitLong = new BuiltInCast(Long::Instance(), "conv.i8", LongCast<char>);
        explicitLong->PushParameterType(Instance());
        explicitCasts.emplace_back(ArgumentHash({ Long::Instance(), this }), explicitLong);

        const auto implicitString = new BuiltInCast(String::Instance(), "call instance string valuetype [System.Runtime]System.Char::ToString()", StringCast<char>);
        implicitString->PushParameterType(this);
        implicitCasts.emplace_back(ArgumentHash({ String::Instance(), this }), implicitString);
        explicitCasts.emplace_back(ArgumentHash({ String::Instance(), this }), implicitString);

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, this, "ceq", Equals<char>);
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::Equals, equals);

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, this, "ceq ldc.i4.0 ceq", NotEquals<char>);
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads.emplace_back(SyntaxKind::NotEquals, notEquals);
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
            if (std::get<0>(function) == hash)
                return std::get<1>(function);

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
            if (std::get<0>(cast) == hash)
                return std::get<1>(cast);

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
            if (std::get<0>(cast) == hash)
                return std::get<1>(cast);

        return nullptr;
    }

    const IOperatorOverload* Character::FindOverload(const SyntaxKind base) const
    {
        return FindBuiltInOverload(base);
    }

    const IBuiltInOverload* Character::FindBuiltInOverload(const SyntaxKind base) const
    {
        for (const auto cast: overloads)
            if (std::get<0>(cast) == base)
                return std::get<1>(cast);

        return nullptr;
    }

    Character::~Character()
    {
        for (const auto function: functions)
            delete std::get<1>(function);

        for (const auto cast: implicitCasts)
            delete std::get<1>(cast);

        for (const auto cast: explicitCasts)
            delete std::get<1>(cast);

        for (const auto overload: overloads)
            delete std::get<1>(overload);
    }
}

