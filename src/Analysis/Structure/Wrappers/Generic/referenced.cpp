#include "referenced.h"

#include <map>
#include <format>

#include "../../DataTypes/data_type_extensions.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Wrappers
{
    Referenced::Referenced(const IDataType* const referencedType) : BuiltInClass(std::format("{}&", referencedType->Name()), Describer::Public), referencedType(referencedType)
    { }

    const Referenced* Referenced::Instance(const IDataType* const dataType)
    {
        static std::map<unsigned long, const Referenced*> map;

        const std::vector types({ dataType });
        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto referenced = new Referenced(dataType);

        map[hash] = referenced;
        return referenced;
    }

    int Referenced::SlotCount() const { return 1; }

    const std::string& Referenced::FullName() const { return name; }

    TypeKind Referenced::Type() const { return TypeKind::Referenced; }

    bool Referenced::Writable() const { return false; }

    const IDataType* Referenced::ReferencedType() const { return referencedType; }

    void Referenced::InitializeMembers()
    { }

    const ICharacteristic* Referenced::FindCharacteristic(const std::string& name) const
    {
        return referencedType->FindCharacteristic(name);
    }

    const IFunction* Referenced::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunctionDefinition* Referenced::FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const
    {
        return referencedType->FindFunction(name, argumentList);
    }

    const IIndexerDefinition* Referenced::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    {
        return referencedType->FindIndexer(argumentList);
    }

    const IFunction* Referenced::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Referenced::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* Referenced::FindOverload(const SyntaxKind base) const
    { return nullptr; }
}
