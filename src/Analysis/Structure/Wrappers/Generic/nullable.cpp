#include "nullable.h"

#include <map>
#include <format>

#include "../../DataTypes/data_type_extensions.h"

#include "../../Global/BuiltIn/built_in_indexer.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_constructor.h"

#include "../Value/boolean.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

constexpr std::string cil_nullable = "[System.Runtime]System.Nullable";

namespace Analysis::Structure::Wrappers
{
    Nullable::Nullable(const IDataType* const nullableType) : BuiltInValueType(cil_nullable, Describer::Public), genericSignature(), nullableType(nullableType), characteristics(), constructors()
    { }

    const Nullable* Nullable::Instance(const IDataType* const dataType)
    {
        static std::map<unsigned long, const Nullable*> map;

        const std::vector types({ dataType });
        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto nullable = new Nullable(dataType);
        nullable->genericSignature = std::format("{}`1<{}>", cil_nullable, dataType->FullName());

        nullable->InitializeMembers();

        map[hash] = nullable;
        return nullable;
    }

    TypeKind Nullable::Type() const { return TypeKind::Nullable; }

    const std::string& Nullable::FullName() const { return genericSignature; }

    void Nullable::InitializeMembers()
    {
        const auto isNull = std::format("call instance bool valuetype {}::get_HasValue()", genericSignature);
        characteristics["IsNull"] = new BuiltInProperty(Describer::Public, "IsNull", &Boolean::Instance(), true, isNull, false, "");

        const auto value = std::format("call instance !0 valuetype {}::get_Value()", genericSignature);
        characteristics["Value"] = new BuiltInProperty(Describer::Public, "Value", nullableType, true, value, false, "");

        const auto constructor = new BuiltInConstructor(this, std::format("call instance void valuetype {}::.ctor(!0)", genericSignature));
        constructor->PushParameterType(nullableType);
        constructors[ArgumentHash(constructor)] = constructor;

        const auto defaultConstructor = new BuiltInConstructor(this, std::format("initobj valuetype {}", genericSignature));
        constructors[ArgumentHash(defaultConstructor)] = defaultConstructor;
    }

    const ICharacteristic* Nullable::FindCharacteristic(const std::string& name) const
    {
        return characteristics.contains(name) ? characteristics.at(name) : nullptr;
    }

    const IFunction* Nullable::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);
        return constructors.contains(hash) ? constructors.at(hash) : nullptr;
    }

    const IFunctionDefinition* Nullable::FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Nullable::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Nullable::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Nullable::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* Nullable::FindOverload(const SyntaxKind base) const
    { return nullptr; }

    Nullable::~Nullable()
    {
        for (const auto& characteristic: characteristics)
            delete characteristic.second;

        for (const auto& constructor: constructors)
            delete constructor.second;
    }
}

