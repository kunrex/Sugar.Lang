#include "value_type.h"

#include "data_type_extensions.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes::DataTypes;

using namespace ParseNodes::DataTypes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

constexpr int word_size = 8;

namespace Analysis::Structure::DataTypes
{
    ValueType::ValueType(const string& name, const Enums::Describer describer) : DataType(name, describer)
    {
        slotCount = -1;
    }

    MemberType ValueType::MemberType() const { return MemberType::ValueType; }

    int ValueType::SlotCount() const
    {
        if (slotCount < 0)
        {
            int totalSize = 0, maxSize = 0;

            for (const auto& characteristic : characteristics)
            {
                const auto size = characteristic.second->CreationType()->SlotCount();
                const auto actual_size = size + (word_size - 1) & ~(word_size - 1);

                totalSize += actual_size;
                if (actual_size > maxSize)
                    maxSize = actual_size;
            }

            slotCount = std::ceil(totalSize + (maxSize - 1) & ~(maxSize - 1) / word_size);
        }

        return slotCount;
    }

    const string& ValueType::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    void ValueType::PushCharacteristic(ICharacteristic* const characteristic)
    {
        characteristics[characteristic->Name()] = characteristic;
    }

    const ICharacteristic* ValueType::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? nullptr : characteristics.at(name);
    }

    void ValueType::PushFunction(IFunctionDefinition* function)
    {
        functions[std::hash<string>()(function->Name()) ^ ArgumentHash(function)] = function;
    }

    const IFunctionDefinition* ValueType::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);
        return functions.contains(hash) ? nullptr : functions.at(hash);
    }

    void ValueType::PushConstructor(IFunction* constructor)
    {
        constructors[ArgumentHash(constructor)] = constructor;
    }

    const IFunction* ValueType::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return constructors.contains(hash) ? nullptr : constructors.at(hash);
    }

    void ValueType::PushIndexer(IIndexerDefinition* indexer)
    {
        indexers[ArgumentHash(indexer)] = indexer;
    }

    const IIndexerDefinition* ValueType::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return indexers.contains(hash) ? nullptr : indexers.at(hash);
    }

    void ValueType::PushImplicitCast(IFunction* cast)
    {
        implicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const IFunction* ValueType::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return implicitCasts.contains(hash) ? nullptr : implicitCasts.at(hash);
    }

    void ValueType::PushExplicitCast(IFunction* cast)
    {
        explicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const IFunction* ValueType::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return explicitCasts.contains(hash) ? nullptr : explicitCasts.at(hash);
    }

    void ValueType::PushOverload(IOperatorOverload* overload)
    {
        overloads[overload->Operator()] = overload;
    }

    const IOperatorOverload* ValueType::FindOverload(const SyntaxKind base) const
    {
        return overloads.at(base);
    }

    ValueType::~ValueType()
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

    StructSource::StructSource(const string& name, const Enums::Describer describer, const DataTypeNode* skeleton) : ValueType(name, describer), UserDefinedType(skeleton)
    { }

    const string& StructSource::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    std::vector<const ICharacteristic*> StructSource::AllCharacteristics() const
    {
        std::vector<const ICharacteristic*> all;
        for (const auto& characteristic : characteristics)
            all.push_back(characteristic.second);

        return all;
    }
}
