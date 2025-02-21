#include "class.h"

#include "data_type_extensions.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes::DataTypes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::DataTypes
{
    Class::Class(const string& name, const Enums::Describer describer) : DataType(name, describer), fullName()
    { }

    MemberType Class::MemberType() const { return MemberType::Class; }

    int Class::SlotCount() const { return 1; }

    const string& Class::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    void Class::PushCharacteristic(Characteristic* const characteristic)
    {
        characteristics[characteristic->Name()] = characteristic;
    }

    const Characteristic* Class::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? nullptr : characteristics.at(name);
    }

    void Class::PushFunction(FunctionDefinition* function)
    {
        functions[std::hash<string>()(function->Name()) ^ ArgumentHash(function)] = function;
    }

    const FunctionDefinition* Class::FindFunction(const string& name, const std::vector<const DataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);
        return functions.contains(hash) ? nullptr : functions.at(hash);
    }

    void Class::PushConstructor(ConstructorDefinition* constructor)
    {
        constructors[ArgumentHash(constructor)] = constructor;
    }

    const ConstructorDefinition* Class::FindConstructor(const std::vector<const DataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return constructors.contains(hash) ? nullptr : constructors.at(hash);
    }

    void Class::PushIndexer(IndexerDefinition* indexer)
    {
        indexers[ArgumentHash(indexer)] = indexer;
    }

    const IndexerDefinition* Class::FindIndexer(const std::vector<const DataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return indexers.contains(hash) ? nullptr : indexers.at(hash);
    }

    void Class::PushImplicitCast(CastDefinition* cast)
    {
        implicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const CastDefinition* Class::FindImplicitCast(const DataType* returnType, const DataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return implicitCasts.contains(hash) ? nullptr : implicitCasts.at(hash);
    }

    void Class::PushExplicitCast(CastDefinition* cast)
    {
        explicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const CastDefinition* Class::FindExplicitCast(const DataType* returnType, const DataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return explicitCasts.contains(hash) ? nullptr : explicitCasts.at(hash);
    }

    void Class::PushOverload(OverloadDefinition* overload)
    {
        overloads[overload->Operator()] = overload;
    }

    const OverloadDefinition* Class::FindOverload(const SyntaxKind base) const
    {
        return overloads.at(base);
    }

    std::vector<const Characteristic*> Class::AllCharacteristics() const
    {
        std::vector<const Characteristic*> all;
        for (const auto& characteristic : characteristics)
            all.push_back(characteristic.second);

        return all;
    }

    Class::~Class()
    {
        for (const auto& characteristic : characteristics)
            delete characteristic.second;

        for (const auto function: functions)
            delete function.second;

        for (const auto constructor: constructors)
            delete constructor.second;

        for (const auto indexer: indexers)
            delete indexer.second;

        for (const auto cast: implicitCasts)
            delete cast.second;

        for (const auto cast: explicitCasts)
            delete cast.second;

        for (const auto& overload: overloads)
            delete overload.second;
    }

    ClassSource::ClassSource(const string& name, const Enums::Describer describer, const DataTypeNode* skeleton) : Class(name, describer), UserDefinedType(skeleton)
    { }

    const string& ClassSource::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }
}


