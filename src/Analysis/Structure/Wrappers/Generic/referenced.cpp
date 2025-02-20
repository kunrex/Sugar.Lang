#include "referenced.h"

#include <map>
#include <format>

#include "../../DataTypes/data_type_extensions.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::DataTypes;

namespace Analysis::Structure::Wrappers
{
    Referenced::Referenced(const DataType* const referencedType) : Class("referenced", Describer::Public), referencedType(referencedType)
    { }

    const Referenced* Referenced::Instance(const DataType* const dataType)
    {
        static std::map<unsigned long, const Referenced*> map;

        const std::vector types({ dataType });
        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto referenced = new Referenced(dataType);
        referenced->referenceName = dataType->FullName() + "&";

        map[hash] = referenced;
        return referenced;
    }

    const std::string& Referenced::FullName() const { return referenceName; }

    const Core::Characteristic* Referenced::FindCharacteristic(const std::string& name) const
    {
        return referencedType->FindCharacteristic(name);
    }

    const Creation::ConstructorDefinition* Referenced::FindConstructor(const std::vector<const DataType*>& argumentList) const
    { return nullptr; }

    const Creation::FunctionDefinition* Referenced::FindFunction(const std::string& name, const std::vector<const DataType*>& argumentList) const
    {
        return referencedType->FindFunction(name, argumentList);
    }

    const Creation::IndexerDefinition* Referenced::FindIndexer(const std::vector<const DataType*>& argumentList) const
    {
        return referencedType->FindIndexer(argumentList);
    }

    const Creation::CastDefinition* Referenced::FindImplicitCast(const DataType* returnType, const DataType* fromType) const
    {
        return referencedType->FindImplicitCast(returnType, fromType);
    }

    const Creation::CastDefinition* Referenced::FindExplicitCast(const DataType* returnType, const DataType* fromType) const
    {
        return referencedType->FindImplicitCast(returnType, fromType);
    }

    const Creation::OverloadDefinition* Referenced::FindOverload(const Tokens::Enums::SyntaxKind base) const
    {
        return referencedType->FindOverload(base);
    }
}
