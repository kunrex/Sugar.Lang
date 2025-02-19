#include "referenced.h"

#include <map>
#include <format>

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Wrappers
{
    Referenced::Referenced(const DataType* nullableType) : DataType("Referenced", Describer::Public), referencedType(nullableType)
    {
        slotCount = referencedType->SlotCount();
    }

    const Referenced* Referenced::Instance(const DataType* dataType)
    {
        static std::map<string, const Referenced*> map;

        if (map.contains(dataType->FullName()))
            return map[dataType->FullName()];

        const auto referenced = new Referenced(dataType);
        map[dataType->FullName()] = referenced;

        referenced->fullName = dataType->FullName();
        return referenced;
    }

    MemberType Referenced::MemberType() const { return MemberType::Class; }

    int Referenced::SlotCount() const { return slotCount; }

    void Referenced::PushCharacteristic(Core::Characteristic* characteristic)
    { }

    const Core::Characteristic* Referenced::FindCharacteristic(const std::string& name) const
    {
        return referencedType->FindCharacteristic(name);
    }

    void Referenced::PushConstructor(Creation::ConstructorDefinition* constructor)
    { }

    const Creation::ConstructorDefinition* Referenced::FindConstructor(const std::vector<const DataType*>& argumentList) const
    { return nullptr; }

    void Referenced::PushFunction(Creation::FunctionDefinition* function)
    { }

    const Creation::FunctionDefinition* Referenced::FindFunction(const std::string& name, const std::vector<const DataType*>& argumentList) const
    {
        return referencedType->FindFunction(name, argumentList);
    }

    void Referenced::PushIndexer(Creation::IndexerDefinition* indexer)
    { }

    const Creation::IndexerDefinition* Referenced::FindIndexer(const std::vector<const DataType*>& argumentList) const
    {
        return referencedType->FindIndexer(argumentList);
    }

    void Referenced::PushImplicitCast(Creation::CastDefinition* cast)
    { }

    const Creation::CastDefinition* Referenced::FindImplicitCast(const DataType* returnType, const DataType* fromType) const
    {
        return referencedType->FindImplicitCast(returnType, fromType);
    }

    void Referenced::PushExplicitCast(Creation::CastDefinition* cast)
    { }

    const Creation::CastDefinition* Referenced::FindExplicitCast(const DataType* returnType, const DataType* fromType) const
    {
        return referencedType->FindImplicitCast(returnType, fromType);
    }

    void Referenced::PushOverload(Creation::OverloadDefinition* overload)
    { }

    const Creation::OverloadDefinition* Referenced::FindOverload(Tokens::Enums::SyntaxKind base) const
    {
        return referencedType->FindOverload(base);
    }
}
