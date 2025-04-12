#include "enum_field.h"

#include "format"

#include "../../DataTypes/enum.h"
#include "../../DataTypes/data_type_extensions.h"

#include "../../Compilation/compilation_result.h"

#include "../../Global/BuiltIn/built_in_cast.h"
#include "../../Global/BuiltIn/built_in_operation.h"

#include "../Value/integer.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Compilation;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Wrappers
{
    CompilationResult Not(const std::vector<CompilationResult>& arguments) { return { &Integer::Instance(), ~std::get<int>(arguments[0].data)} ; }
    CompilationResult BitwiseAnd(const std::vector<CompilationResult>& arguments) { return { &Integer::Instance(), std::get<int>(arguments[0].data) & std::get<int>(arguments[1].data)} ; }
    CompilationResult BitwiseOr(const std::vector<CompilationResult>& arguments) { return { &Integer::Instance(), std::get<int>(arguments[0].data) | std::get<int>(arguments[1].data)} ; }
    CompilationResult RightShift(const std::vector<CompilationResult>& arguments) { return { &Integer::Instance(), std::get<int>(arguments[0].data) >> std::get<int>(arguments[1].data)} ; }
    CompilationResult LeftShift(const std::vector<CompilationResult>& arguments) { return { &Integer::Instance(), std::get<int>(arguments[0].data) << std::get<int>(arguments[1].data)} ; }
    CompilationResult BitwiseXor(const std::vector<CompilationResult>& arguments) { return { &Integer::Instance(), std::get<int>(arguments[0].data) ^ std::get<int>(arguments[1].data)} ; }

    EnumField::EnumField(const IDataType* const enumType) : BuiltInValueType(enumType->Name(), Describer::Public), SingletonService(), enumType(enumType), explicitCasts(), overloads()
    { }

    const EnumField* EnumField::Instance(const IDataType* const enumType)
    {
        static std::map<uintptr_t, const EnumField*> map;

        const auto hash = reinterpret_cast<uintptr_t>(enumType);

        if (map.contains(hash))
            return map.at(hash);

        const auto enumField = new EnumField(enumType);
        enumField->InitializeMembers();

        map[hash] = enumField;
        return enumField;
    }

    int EnumField::SlotCount() const { return 1; }

    TypeKind EnumField::Type() const { return TypeKind::EnumField; }

    const std::string& EnumField::FullName() const { return enumType->FullName(); }

    void EnumField::InitializeMembers()
    {
        const auto explicitInteger = new BuiltInCast(&Integer::Instance(), "conv.i4", nullptr);
        explicitInteger->PushParameterType(this);
        explicitCasts[DataTypes::ArgumentHash(explicitInteger)] = explicitInteger;

        const auto explicitString = new BuiltInCast(&Integer::Instance(), std::format("box {} call instance string [mscorlib]System.Boolean::ToString()", enumType->FullName()), nullptr);
        explicitString->PushParameterType(this);
        explicitCasts[ArgumentHash(explicitString)] = explicitString;

        const auto bitwiseNot = new BuiltInOperation(SyntaxKind::BitwiseNot, this, "not", Not);
        bitwiseNot->PushParameterType(this);
        overloads[SyntaxKind::BitwiseNot] = bitwiseNot;

        const auto bitwiseAnd = new BuiltInOperation(SyntaxKind::BitwiseAnd, this, "and", BitwiseAnd);
        bitwiseAnd->PushParameterType(this);
        bitwiseAnd->PushParameterType(this);
        overloads[SyntaxKind::BitwiseAnd] = bitwiseAnd;

        const auto bitwiseOr = new BuiltInOperation(SyntaxKind::BitwiseOr, this, "or", BitwiseOr);
        bitwiseOr->PushParameterType(this);
        bitwiseOr->PushParameterType(this);
        overloads[SyntaxKind::BitwiseOr] = bitwiseOr;

        const auto bitwiseXor = new BuiltInOperation(SyntaxKind::BitwiseXor, this, "xor", BitwiseXor);
        bitwiseXor->PushParameterType(this);
        bitwiseXor->PushParameterType(&Integer::Instance());
        overloads[SyntaxKind::BitwiseXor] = bitwiseXor;

        const auto rightShift = new BuiltInOperation(SyntaxKind::RightShift, this, "shr", RightShift);
        rightShift->PushParameterType(this);
        rightShift->PushParameterType(&Integer::Instance());
        overloads[SyntaxKind::RightShift] = rightShift;

        const auto leftShift = new BuiltInOperation(SyntaxKind::LeftShift, this, "shl", LeftShift);
        leftShift->PushParameterType(this);
        leftShift->PushParameterType(&Integer::Instance());
        overloads[SyntaxKind::LeftShift] = leftShift;
    }

    const ICharacteristic* EnumField::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? nullptr : characteristics.at(name);
    }

    const IFunctionDefinition* EnumField::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* EnumField::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* EnumField::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* EnumField::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* EnumField::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash({ returnType , fromType });
        return explicitCasts.contains(hash) ? nullptr : explicitCasts.at(hash);
    }

    const IOperatorOverload* EnumField::FindOverload(const SyntaxKind base) const
    {
        return overloads.contains(base) ? nullptr : overloads.at(base);
    }

    EnumField::~EnumField()
    {
        for (const auto cast : explicitCasts)
            delete cast.second;

        for (const auto overload: overloads)
            delete overload.second;
    }
}