#include "boolean.h"

#include "../../DataTypes/data_type_extensions.h"

#include "long.h"
#include "integer.h"
#include "short.h"

#include "../Reference/string.h"

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_operation.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

constexpr std::string cil_boolean = "[System.Runtime]System.Boolean";

namespace Analysis::Structure::Wrappers
{
    Boolean::Boolean() : BuiltInValueType(cil_boolean, Enums::Describer::Public), SingletonService(), implicitCasts(), explicitCasts(), overloads()
    { }

    int Boolean::SlotCount() const { return 1; }

    TypeKind Boolean::Type() const { return TypeKind::Boolean; }

    void Boolean::InitializeMembers()
    {
        const auto explicitShort = new BuiltInCast(&Short::Instance(), "conv.i2");
        explicitShort->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Short::Instance(), &Instance()})] = explicitShort;

        const auto explicitInteger = new BuiltInCast(&Integer::Instance(), "conv.i4");
        explicitInteger->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Integer::Instance(), &Instance()})] = explicitShort;

        const auto explicitLong = new BuiltInCast(&Long::Instance(), "conv.i8");
        explicitLong->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Long::Instance(), &Instance()})] = explicitShort;

        const auto explicitString = new BuiltInCast(&String::Instance(), "call instance string valuetype [System.Runtime]System.Boolean::ToString()");
        explicitString->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &String::Instance(), &Instance()})] = explicitShort;

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, &Instance(), "ceq");
        equals->PushParameterType(&Instance());
        equals->PushParameterType(&Instance());
        overloads[SyntaxKind::Equals] = equals;

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, &Instance(), "ceq ldc.i4.0 ceq");
        notEquals->PushParameterType(&Instance());
        notEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::NotEquals] = notEquals;

        const auto logicalNot = new BuiltInOperation(SyntaxKind::Not, &Instance(), "ldc.i4.0 ceq");
        logicalNot->PushParameterType(&Instance());
        overloads[SyntaxKind::Not] = logicalNot;

        const auto logicalAnd = new BuiltInOperation(SyntaxKind::And, &Instance(), "and");
        logicalAnd->PushParameterType(&Instance());
        logicalAnd->PushParameterType(&Instance());
        overloads[SyntaxKind::And] = logicalAnd;

        const auto logicalOr = new BuiltInOperation(SyntaxKind::Or, &Instance(), "or");
        logicalOr->PushParameterType(&Instance());
        logicalOr->PushParameterType(&Instance());
        overloads[SyntaxKind::Or] = logicalOr;
    }

    const ICharacteristic* Boolean::FindCharacteristic(const string& name) const
    { return nullptr; }

    const IFunctionDefinition* Boolean::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Boolean::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Boolean::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Boolean::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });
        return implicitCasts.contains(hash) ? nullptr : implicitCasts.at(hash);
    }

    const IFunction* Boolean::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });
        return explicitCasts.contains(hash) ? nullptr : explicitCasts.at(hash);
    }

    const IOperatorOverload* Boolean::FindOverload(const SyntaxKind base) const
    {
        return overloads.contains(base) ? nullptr : overloads.at(base);
    }

    Boolean::~Boolean()
    {
        for (const auto cast: implicitCasts)
            delete cast.second;

        for (const auto cast: explicitCasts)
            delete cast.second;

        for (const auto overload: overloads)
            delete overload.second;
    }
}
