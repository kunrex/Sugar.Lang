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

const string cil_nullable = "[System.Runtime]System.Nullable";

namespace Analysis::Structure::Wrappers
{
    Nullable::Nullable(const IDataType* const nullableType) : BuiltInValueType(cil_nullable, Describer::Public), SingletonService(), genericSignature(), nullableType(nullableType), constructors()
    { }

    const Nullable* Nullable::Instance(const IDataType* const dataType)
    {
        static std::map<uintptr_t, const Nullable*> map;
        const auto hash = reinterpret_cast<uintptr_t>(dataType);

        if (map.contains(hash))
            return map.at(hash);

        const auto nullable = new Nullable(dataType);
        nullable->genericSignature = std::format("{}`1<{}>", cil_nullable, dataType->FullName());

        nullable->BindGlobal();

        map[hash] = nullable;
        return nullable;
    }

    TypeKind Nullable::Type() const { return TypeKind::Nullable; }

    const std::string& Nullable::FullName() const { return genericSignature; }

    void Nullable::BindGlobal()
    {
        const auto isNull = std::format("call instance bool valuetype {}::get_HasValue()", genericSignature);
        characteristics.push_back(new BuiltInProperty("IsNull", Describer::Public, Boolean::Instance(), true, isNull, false, ""));

        const auto value = std::format("call instance !0 valuetype {}::get_Value()", genericSignature);
        characteristics.push_back(new BuiltInProperty("Value", Describer::Public, nullableType, true, value, false, ""));

        const auto constructor = new BuiltInConstructor(this, std::format("call instance void valuetype {}::.ctor(!0)", genericSignature));
        constructor->PushParameterType(nullableType);
        constructors.emplace_back(ArgumentHash(constructor), constructor);

        const auto defaultConstructor = new BuiltInConstructor(this, "initobj valuetype {}" + genericSignature);
        constructors.emplace_back(ArgumentHash(defaultConstructor), defaultConstructor);
    }

    const ICharacteristic* Nullable::FindCharacteristic(const std::string& name) const
    {
        for (const auto characteristic : characteristics)
            if (characteristic->Name() == name)
                return characteristic;

        return nullptr;
    }

    const IConstructor* Nullable::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    {
        const auto hash = ArgumentHash(argumentList);

        for (const auto constructor : constructors)
            if (std::get<0>(constructor) == hash)
                return std::get<1>(constructor);

        return nullptr;
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
        for (const auto constructor: constructors)
            delete std::get<1>(constructor);
    }
}

