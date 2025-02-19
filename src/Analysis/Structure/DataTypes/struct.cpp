#include "struct.h"

#include "data_type_extensions.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes::DataTypes;

using namespace ParseNodes::DataTypes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

constexpr int word_size = 8;

namespace Analysis::Structure::DataTypes
{
    Struct::Struct(const string& name, const Enums::Describer describer) : DataType(name, describer)
    {
        slotCount = 0;
    }

    MemberType Struct::MemberType() const { return MemberType::Struct; }

    int Struct::SlotCount() const
    {
        if (slotCount == 0)
        {
            int totalSize = 0;
            int maxAlignment = 0;

            for (const auto& characteristic : characteristics)
            {
                const auto fieldSize = characteristic.second->CreationType()->SlotCount();
                const auto fieldAlignment = std::min(fieldSize, word_size);

                totalSize = (totalSize + (fieldAlignment - 1)) & ~(fieldAlignment - 1)  + fieldSize;
                maxAlignment = std::max(maxAlignment, fieldAlignment);
            }

            slotCount = (totalSize + (word_size - 1)) / word_size;
        }

        return slotCount;
    }

    const std::string& Struct::FullName() const { return name; }

    void Struct::PushCharacteristic(Characteristic* const characteristic)
    {
        characteristics[characteristic->Name()] = characteristic;
    }

    const Characteristic* Struct::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? nullptr : characteristics.at(name);
    }

    void Struct::PushFunction(FunctionDefinition* function)
    {
        functions[std::hash<string>()(function->Name()) ^ ArgumentHash(function)] = function;
    }

    const FunctionDefinition* Struct::FindFunction(const string& name, const std::vector<const DataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);
        return functions.contains(hash) ? nullptr : functions.at(hash);
    }

    void Struct::PushConstructor(ConstructorDefinition* constructor)
    {
        constructors[ArgumentHash(constructor)] = constructor;
    }

    const ConstructorDefinition* Struct::FindConstructor(const std::vector<const DataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return constructors.contains(hash) ? nullptr : constructors.at(hash);
    }

    void Struct::PushIndexer(IndexerDefinition* indexer)
    {
        indexers[ArgumentHash(indexer)] = indexer;
    }

    const IndexerDefinition* Struct::FindIndexer(const std::vector<const DataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return indexers.contains(hash) ? nullptr : indexers.at(hash);
    }

    void Struct::PushImplicitCast(CastDefinition* cast)
    {
        implicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const CastDefinition* Struct::FindImplicitCast(const DataType* returnType, const DataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return implicitCasts.contains(hash) ? nullptr : implicitCasts.at(hash);
    }

    void Struct::PushExplicitCast(CastDefinition* cast)
    {
        explicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const CastDefinition* Struct::FindExplicitCast(const DataType* returnType, const DataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return explicitCasts.contains(hash) ? nullptr : explicitCasts.at(hash);
    }

    void Struct::PushOverload(OverloadDefinition* overload)
    {
        overloads[overload->Operator()] = overload;
    }

    const OverloadDefinition* Struct::FindOverload(const SyntaxKind base) const
    {
        return overloads.at(base);
    }

    std::vector<const Characteristic*> Struct::AllCharacteristics() const
    {
        std::vector<const Characteristic*> all;
        for (const auto& characteristic : characteristics)
            all.push_back(characteristic.second);

        return all;
    }

    Struct::~Struct()
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

    StructSource::StructSource(const string& name, const Enums::Describer describer, const DataTypeNode* skeleton) : Struct(name, describer), UserDefinedType(skeleton)
    { }

    const string& StructSource::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }
}
