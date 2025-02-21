#include "enum.h"

#include <format>

#include "data_type_extensions.h"

#include "../Global/BuiltIn/built_in_method.h"
#include "../Global/Functions/method_function.h"

#include "../Wrappers/Generic/array.h"

using namespace std;

using namespace Tokens::Enums;

using namespace ParseNodes::DataTypes;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::Creation;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::DataTypes
{
    Enum::Enum(const string& name, const Enums::Describer describer, const DataTypeNode* skeleton, DataType* const valueImplementation) : DataType(name, describer | Describer::Static), UserDefinedType(skeleton), valueImplementation(valueImplementation)
    { }

    MemberType Enum::MemberType() const { return MemberType::Enum; }

    int Enum::SlotCount() const { return 1; }

    const string& Enum::FullName() const
    {
        if (fullName.empty() && parent != nullptr)
            fullName = parent->FullName() + "." + name;

        return fullName;
    }

    DataType* Enum::ValueImplementation() const { return valueImplementation; }

    void Enum::PushCharacteristic(Characteristic* const characteristic)
    {
        characteristics[characteristic->Name()] = characteristic;
    }

    const Characteristic* Enum::FindCharacteristic(const string& name) const
    {
        return characteristics.contains(name) ? nullptr : characteristics.at(name);
    }

    void Enum::PushFunction(FunctionDefinition* function)
    {
        if (values == nullptr)
            values = function;
    }

    const FunctionDefinition* Enum::FindFunction(const string& name, const std::vector<const DataType*>& argumentList) const
    {
        if (values == nullptr)
            return nullptr;

        if (name != values->Name())
            return nullptr;

        if (!argumentList.empty())
            return nullptr;

        return values;
    }

    void Enum::PushConstructor(ConstructorDefinition* constructor)
    { }

    const ConstructorDefinition* Enum::FindConstructor(const std::vector<const DataType*>& argumentList) const
    {
        return nullptr;
    }

    void Enum::PushIndexer(IndexerDefinition* indexer)
    { }

    const IndexerDefinition* Enum::FindIndexer(const std::vector<const DataType*>& argumentList) const
    {
        return nullptr;
    }

    void Enum::PushImplicitCast(CastDefinition* cast)
    { }

    const CastDefinition* Enum::FindImplicitCast(const DataType* returnType, const DataType* fromType) const
    {
        return nullptr;
    }

    void Enum::PushExplicitCast(CastDefinition* cast)
    { }

    const CastDefinition* Enum::FindExplicitCast(const DataType* returnType, const DataType* fromType) const
    {
        return nullptr;
    }

    void Enum::PushOverload(OverloadDefinition* overload)
    { }

    const OverloadDefinition* Enum::FindOverload(const SyntaxKind base) const
    {
        return nullptr;
    }

    std::vector<const Characteristic*> Enum::AllCharacteristics() const
    {
        std::vector<const Characteristic*> all;
        for (const auto& characteristic : characteristics)
            all.push_back(characteristic.second);

        return all;
    }

    Enum::~Enum()
    {
        for (const auto& characteristic : characteristics)
            delete characteristic.second;
    }
}
