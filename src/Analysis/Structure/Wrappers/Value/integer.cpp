#include "integer.h"

#include "../../DataTypes/data_type_extensions.h"

#include "short.h"
#include "long.h"
#include "./float.h"
#include "double.h"
#include "boolean.h"
#include "../Reference/string.h"
#include "../Generic/referenced.h"

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_method.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_operation.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

constexpr std::string cil_integer = "[System.Runtime]System.Int32";

namespace Analysis::Structure::Wrappers
{
    Integer::Integer() : BuiltInValueType(cil_integer, Describer::Public), SingletonService(), characteristics(), tryParse(nullptr), implicitCasts(), explicitCasts(), overloads()
    { }

    int Integer::SlotCount() const { return 1; }

    TypeKind Integer::Type() const { return TypeKind::Int; }

    void Integer::InitializeMembers()
    {
        characteristics["Max"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "Max", &Instance(), true, "ldc.i4 2147483647", false, "");
        characteristics["Min"] = new BuiltInProperty(Describer::Public | Describer::Constexpr, "Min", &Instance(), true, "ldc.i4 -2147483647", false, "");

        tryParse = new BuiltInMethod("TryParse", Describer::PublicStatic, &Boolean::Instance(), "bool valuetype [System.Runtime]System.Int32::TryParse(string, int32&)");
        tryParse->PushParameterType(&String::Instance());
        tryParse->PushParameterType(Referenced::Instance(&Instance()));

        const auto explicitShort = new BuiltInCast(&Short::Instance(), "conv.i2");
        explicitShort->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Short::Instance(), &Instance() })] = explicitShort;

        const auto implicitLong = new BuiltInCast(&Long::Instance(), "conv.i8");
        implicitLong->PushParameterType(&Instance());
        implicitCasts[ArgumentHash({ &Long::Instance(), &Instance() })] = implicitLong;
        explicitCasts[ArgumentHash({ &Long::Instance(), &Instance() })] = implicitLong;

        const auto explicitFloat = new BuiltInCast(&Float::Instance(), "conv.r4");
        explicitFloat->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &Float::Instance(), &Instance() })] = explicitFloat;

        const auto implicitDouble = new BuiltInCast(&Double::Instance(), "conv.r8");
        implicitDouble->PushParameterType(&Instance());
        implicitCasts[ArgumentHash({ { &Double::Instance(), &Instance() }})] = implicitDouble;
        explicitCasts[ArgumentHash({ { &Double::Instance(), &Instance() }})] = implicitDouble;

        const auto explicitString = new BuiltInCast(&String::Instance(), "call instance string valuetype [System.Runtime]System.Int32::ToString()");
        explicitString->PushParameterType(&Instance());
        explicitCasts[ArgumentHash({ &String::Instance(), &Instance() })] = explicitString;

        const auto equals = new BuiltInOperation(SyntaxKind::Equals, &Boolean::Instance(), "ceq");
        equals->PushParameterType(&Instance());
        equals->PushParameterType(&Instance());
        overloads[SyntaxKind::Equals] = equals;

        const auto notEquals = new BuiltInOperation(SyntaxKind::NotEquals, &Boolean::Instance(), "ceq ldc.i4.0 ceq");
        notEquals->PushParameterType(&Instance());
        notEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::NotEquals] = notEquals;

        const auto addition = new BuiltInOperation(SyntaxKind::Addition, &Instance(), "add");
        addition->PushParameterType(&Instance());
        addition->PushParameterType(&Instance());
        overloads[SyntaxKind::Addition] = addition;

        const auto subtraction = new BuiltInOperation(SyntaxKind::Subtraction, &Instance(), "sub");
        subtraction->PushParameterType(&Instance());
        subtraction->PushParameterType(&Instance());
        overloads[SyntaxKind::Subtraction] = subtraction;

        const auto multiplication = new BuiltInOperation(SyntaxKind::Multiplication, &Instance(), "mul");
        multiplication->PushParameterType(&Instance());
        multiplication->PushParameterType(&Instance());
        overloads[SyntaxKind::Multiplication] = multiplication;

        const auto division = new BuiltInOperation(SyntaxKind::Division, &Instance(), "div");
        division->PushParameterType(&Instance());
        division->PushParameterType(&Instance());
        overloads[SyntaxKind::Division] = division;

        const auto remainder = new BuiltInOperation(SyntaxKind::Modulus, &Instance(), "rem");
        remainder->PushParameterType(&Instance());
        remainder->PushParameterType(&Instance());
        overloads[SyntaxKind::Modulus] = remainder;

        const auto plus = new BuiltInOperation(SyntaxKind::Plus, &Instance(), "");
        plus->PushParameterType(&Instance());
        overloads[SyntaxKind::Plus] = plus;

        const auto negation = new BuiltInOperation(SyntaxKind::Minus, &Instance(), "neg");
        negation->PushParameterType(&Instance());
        overloads[SyntaxKind::Minus] = negation;

        const auto increment = new BuiltInOperation(SyntaxKind::Increment, &Instance(), "ldc.r8 1.0 add");
        increment->PushParameterType(&Instance());
        increment->PushParameterType(&Instance());
        overloads[SyntaxKind::Increment] = increment;

        const auto decrement = new BuiltInOperation(SyntaxKind::Decrement, &Instance(), "ldc.r8 1.0 sub");
        decrement->PushParameterType(&Instance());
        decrement->PushParameterType(&Instance());
        overloads[SyntaxKind::Decrement] = decrement;

        const auto greater = new BuiltInOperation(SyntaxKind::GreaterThan, &Boolean::Instance(), "cgt");
        greater->PushParameterType(&Instance());
        greater->PushParameterType(&Instance());
        overloads[SyntaxKind::GreaterThan] = greater;

        const auto lesser = new BuiltInOperation(SyntaxKind::LesserThan, &Boolean::Instance(), "clt");
        lesser->PushParameterType(&Instance());
        lesser->PushParameterType(&Instance());
        overloads[SyntaxKind::LesserThan] = lesser;

        const auto greaterEquals = new BuiltInOperation(SyntaxKind::GreaterThanEquals, &Boolean::Instance(), "clt ldc.i4.0 ceq");
        greaterEquals->PushParameterType(&Instance());
        greaterEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::GreaterThanEquals] = greaterEquals;

        const auto lesserEquals = new BuiltInOperation(SyntaxKind::LesserThanEquals, &Boolean::Instance(), "cgt ldc.i4.0 ceq");
        lesserEquals->PushParameterType(&Instance());
        lesserEquals->PushParameterType(&Instance());
        overloads[SyntaxKind::LesserThanEquals] = lesserEquals;

        const auto bitwiseNot = new BuiltInOperation(SyntaxKind::BitwiseNot, &Instance(), "not");
        bitwiseNot->PushParameterType(&Instance());
        overloads[SyntaxKind::BitwiseNot] = bitwiseNot;

        const auto bitwiseAnd = new BuiltInOperation(SyntaxKind::BitwiseAnd, &Instance(), "and");
        bitwiseAnd->PushParameterType(&Instance());
        bitwiseAnd->PushParameterType(&Instance());
        overloads[SyntaxKind::BitwiseAnd] = bitwiseAnd;

        const auto bitwiseOr = new BuiltInOperation(SyntaxKind::BitwiseOr, &Instance(), "or");
        bitwiseOr->PushParameterType(&Instance());
        bitwiseOr->PushParameterType(&Instance());
        overloads[SyntaxKind::BitwiseOr] = bitwiseOr;

        const auto bitwiseXor = new BuiltInOperation(SyntaxKind::BitwiseXor, &Instance(), "xor");
        bitwiseXor->PushParameterType(&Instance());
        bitwiseXor->PushParameterType(&Instance());
        overloads[SyntaxKind::BitwiseXor] = bitwiseXor;

        const auto rightShift = new BuiltInOperation(SyntaxKind::RightShift, &Instance(), "shr");
        rightShift->PushParameterType(&Instance());
        rightShift->PushParameterType(&Instance());
        overloads[SyntaxKind::RightShift] = rightShift;

        const auto leftShift = new BuiltInOperation(SyntaxKind::LeftShift, &Instance(), "shl");
        leftShift->PushParameterType(&Instance());
        leftShift->PushParameterType(&Instance());
        overloads[SyntaxKind::LeftShift] = leftShift;
    }

    const ICharacteristic* Integer::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? nullptr : characteristics.at(name);
    }

    const IFunctionDefinition* Integer::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        if (name != "TryParse" || ArgumentHash(argumentList) != ArgumentHash(tryParse))
            return nullptr;

        return tryParse;
    }

    const IFunction* Integer::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Integer::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Integer::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });
        return implicitCasts.contains(hash) ? nullptr : implicitCasts.at(hash);
    }

    const IFunction* Integer::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });
        return explicitCasts.contains(hash) ? nullptr : explicitCasts.at(hash);
    }

    const IOperatorOverload* Integer::FindOverload(const SyntaxKind base) const
    {
        return overloads.contains(base) ? nullptr : overloads.at(base);
    }

    Integer::~Integer()
    {
        for (const auto& characteristic: characteristics)
            delete characteristic.second;

        delete tryParse;

        for (const auto cast: implicitCasts)
            delete cast.second;

        for (const auto cast: explicitCasts)
            delete cast.second;

        for (const auto overload: overloads)
            delete overload.second;
    }
}


