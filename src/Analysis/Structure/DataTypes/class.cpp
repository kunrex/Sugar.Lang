#include "class.h"

#include "data_type_extensions.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::DataTypes
{
    Class::Class(const string& name, const Enums::Describer describer) : DataType(name, describer)
    { }

    MemberType Class::MemberType() const { return MemberType::Class; }

    int Class::SlotCount() const { return 1; }

    BuiltInClass::BuiltInClass(const std::string& name, const Enums::Describer describer) : Class(name, describer)
    { }

    const string& BuiltInClass::FullName() const { return name; }

    ClassSource::ClassSource(const string& name, const Enums::Describer describer, const IParseNode* skeleton) : Class(name, describer), skeleton(skeleton), fullName()
    { }


    TypeKind ClassSource::Type() const { return TypeKind::Custom; }

    const string& ClassSource::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    const IParseNode* ClassSource::Skeleton() const { return skeleton; }

    void ClassSource::PushCharacteristic(ICharacteristic* const characteristic)
    {
        characteristics[characteristic->Name()] = characteristic;
    }

    const ICharacteristic* ClassSource::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? nullptr : characteristics.at(name);
    }

    void ClassSource::PushFunction(IFunctionDefinition* const function)
    {
        functions[std::hash<string>()(function->Name()) ^ ArgumentHash(function)] = function;
    }

    const IFunctionDefinition* ClassSource::FindFunction(const string& name, const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = std::hash<string>()(name) ^ ArgumentHash(argumentList);
        return functions.contains(hash) ? nullptr : functions.at(hash);
    }

    void ClassSource::PushConstructor(IFunction* const constructor)
    {
        IFunction* s = constructor;

        constructors[ArgumentHash(constructor)] = constructor;
    }

    const IFunction* ClassSource::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return constructors.contains(hash) ? nullptr : constructors.at(hash);
    }

    void ClassSource::PushIndexer(IIndexerDefinition* indexer)
    {
        indexers[ArgumentHash(indexer)] = indexer;
    }

    const IIndexerDefinition* ClassSource::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return indexers.contains(hash) ? nullptr : indexers.at(hash);
    }

    void ClassSource::PushImplicitCast(IFunction* cast)
    {
        implicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const IFunction* ClassSource::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return implicitCasts.contains(hash) ? nullptr : implicitCasts.at(hash);
    }

    void ClassSource::PushExplicitCast(IFunction* cast)
    {
        explicitCasts[ArgumentHash(std::vector({ cast->CreationType(), cast->ParameterAt(0)}))] = cast;
    }

    const IFunction* ClassSource::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    {
        const auto hash = ArgumentHash(std::vector({ returnType, fromType}));
        return explicitCasts.contains(hash) ? nullptr : explicitCasts.at(hash);
    }

    void ClassSource::PushOverload(IOperatorOverload* overload)
    {
        overloads[overload->Operator()] = overload;
    }

    const IOperatorOverload* ClassSource::FindOverload(const SyntaxKind base) const
    {
        return overloads.at(base);
    }

    std::vector<ICharacteristic*> ClassSource::AllCharacteristics() const
    {
        std::vector<ICharacteristic*> all;

        for (const auto& characteristic : characteristics)
            all.push_back(characteristic.second);

        return all;
    }

    std::vector<IScoped*> ClassSource::AllScoped() const
    {
        std::vector<IScoped*> all;

        for (const auto function: functions)
            all.push_back(function.second);

        for (const auto constructor: constructors)
            all.push_back(constructor.second);

        for (const auto cast: implicitCasts)
            all.push_back(cast.second);

        for (const auto cast: explicitCasts)
            all.push_back(cast.second);

        for (const auto& overload: overloads)
            delete overload.second;

        return all;
    }

    ClassSource::~ClassSource()
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
}


