#include "enum.h"

#include <format>

#include "data_type_extensions.h"

#include "../Global/BuiltIn/built_in_method.h"
#include "../Global/Functions/method_function.h"

#include "../Wrappers/Generic/array.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Wrappers;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::DataTypes
{
    Enum::Enum(const string& name, const Enums::Describer describer, const IParseNode* skeleton) : DataType(name, describer | Describer::Static), skeleton(skeleton), fullName(), explicitCasts()
    { }

    MemberType Enum::MemberType() const { return MemberType::Enum; }

    int Enum::SlotCount() const { return 1; }

    TypeKind Enum::Type() const { return TypeKind::Custom; }

    const string& Enum::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    const IParseNode* Enum::Skeleton() const { return skeleton; }

    unsigned long Enum::ConstructorCount() const { return 0; }

    void Enum::PushCharacteristic(ICharacteristic* const characteristic)
    {
        characteristics[characteristic->Name()] = characteristic;
    }

    const ICharacteristic* Enum::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? nullptr : characteristics.at(name);
    }

    void Enum::PushFunction(IFunctionDefinition* const function)
    { }

    const IFunctionDefinition* Enum::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr;}

    void Enum::PushConstructor(IFunction* constructor)
    { }

    const IFunction* Enum::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        return nullptr;
    }

    void Enum::PushIndexer(IIndexerDefinition* indexer)
    { }

    const IIndexerDefinition* Enum::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        return nullptr;
    }

    void Enum::PushImplicitCast(IFunction* cast)
    { }

    const IFunction* Enum::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        return nullptr;
    }

    void Enum::PushExplicitCast(IFunction* cast)
    {
        explicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const IFunction* Enum::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return explicitCasts.contains(hash) ? nullptr : explicitCasts.at(hash);
    }

    void Enum::PushOverload(IOperatorOverload* overload)
    { }

    const IOperatorOverload* Enum::FindOverload(const SyntaxKind base) const
    {
        return nullptr;
    }

    std::vector<ICharacteristic*> Enum::AllCharacteristics() const
    {
        std::vector<ICharacteristic*> all;
        for (const auto& characteristic : characteristics)
            all.push_back(characteristic.second);

        return all;
    }

    std::vector<IScoped*> Enum::AllScoped() const
    {
        return { };
    }

    void Enum::Print(const string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Enum: " << name << std::endl;
    }

    Enum::~Enum()
    {
        for (const auto& characteristic : characteristics)
            delete characteristic.second;

        for (const auto& cast: explicitCasts)
            delete cast.second;
    }
}
