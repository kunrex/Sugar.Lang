#include "value_type.h"

#include "data_type_extensions.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
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

    const ICharacteristic* ValueType::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? nullptr : characteristics.at(name);
    }

    ValueType::~ValueType()
    {
        for (const auto& characteristic : characteristics)
            delete characteristic.second;
    }

    BuiltInValueType::BuiltInValueType(const std::string& name, const Enums::Describer describer) : ValueType(name, describer)
    { }

    const string& BuiltInValueType::FullName() const { return name; }

    StructSource::StructSource(const string& name, const Enums::Describer describer, const IParseNode* const skeleton) : ValueType(name, describer), skeleton(skeleton), fullName()
    { }

    TypeKind StructSource::Type() const { return TypeKind::Custom; }

    const string& StructSource::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    const IParseNode* StructSource::Skeleton() const { return skeleton; }

    unsigned long StructSource::ConstructorCount() const { return constructors.size(); }

    void StructSource::PushCharacteristic(ICharacteristic* const characteristic)
    {
        characteristics[characteristic->Name()] = characteristic;
    }

    void StructSource::PushFunction(IFunctionDefinition* function)
    {
        functions[std::hash<string>()(function->Name()) ^ ArgumentHash(function)] = function;
    }

    const IFunctionDefinition* StructSource::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);
        return functions.contains(hash) ? nullptr : functions.at(hash);
    }

    void StructSource::PushConstructor(IFunction* constructor)
    {
        constructors[ArgumentHash(constructor)] = constructor;
    }

    const IFunction* StructSource::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return constructors.contains(hash) ? nullptr : constructors.at(hash);
    }

    void StructSource::PushIndexer(IIndexerDefinition* indexer)
    {
        indexers[ArgumentHash(indexer)] = indexer;
    }

    const IIndexerDefinition* StructSource::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return indexers.contains(hash) ? nullptr : indexers.at(hash);
    }

    void StructSource::PushImplicitCast(IFunction* cast)
    {
        implicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const IFunction* StructSource::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return implicitCasts.contains(hash) ? nullptr : implicitCasts.at(hash);
    }

    void StructSource::PushExplicitCast(IFunction* cast)
    {
        explicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const IFunction* StructSource::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return explicitCasts.contains(hash) ? nullptr : explicitCasts.at(hash);
    }

    void StructSource::PushOverload(IOperatorOverload* overload)
    {
        overloads[overload->Operator()] = overload;
    }

    const IOperatorOverload* StructSource::FindOverload(const SyntaxKind base) const
    {
        return overloads.at(base);
    }

    std::vector<ICharacteristic*> StructSource::AllCharacteristics() const
    {
        std::vector<ICharacteristic*> all;
        for (const auto& characteristic : characteristics)
            all.push_back(characteristic.second);

        return all;
    }

    std::vector<IScoped*> StructSource::AllScoped() const
    {
        std::vector<IScoped*> all(functions.size());

        for (const auto function: functions)
            all.push_back(dynamic_cast<IScoped*>(function.second));

        for (const auto constructor: constructors)
            all.push_back(dynamic_cast<IScoped*>(constructor.second));

        for (const auto cast: implicitCasts)
            all.push_back(dynamic_cast<IScoped*>(cast.second));

        for (const auto cast: explicitCasts)
        {
            if (const auto definition = cast.second; definition->MemberType() == MemberType::ExplicitCast)
                all.push_back(dynamic_cast<IScoped*>(definition));
        }

        for (const auto overload: overloads)
            all.push_back(dynamic_cast<IScoped*>(overload.second));

        return all;
    }

    void StructSource::Print(const string& indent, const bool last) const
    {
        std::cout << indent << (last ? "\\-" : "|-") << "Struct: " << name << std::endl;
    }

    StructSource::~StructSource()
    {
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
}
