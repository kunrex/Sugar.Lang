#include "nullable.h"

#include <map>
#include <format>

#include "../Value/boolean.h"

#include "../../DataTypes/data_type_extensions.h"

#include "../../Global/Properties/property.h"
#include "../../Global/Functions/constructor.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_nullable = "[System.Runtime]System.Nullable";

namespace Analysis::Structure::Wrappers
{
    Nullable::Nullable(const IDataType* const nullableType) : ImplicitValueType(cil_nullable, Describer::Public), SingletonService(), nullableType(nullableType), characteristics()
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

    int Nullable::SlotCount() const
    {
        if (slotCount < 0)
        {
            int totalSize = 0, maxSize = 0;

            for (const auto& characteristic : characteristics)
            {
                const auto size = characteristic->CreationType()->SlotCount();
                const auto actual_size = size + (word_size - 1) & ~(word_size - 1);

                totalSize += actual_size;
                if (actual_size > maxSize)
                    maxSize = actual_size;
            }

            slotCount = std::ceil(totalSize + (maxSize - 1) & ~(maxSize - 1) / word_size);
        }

        return slotCount;
    }

    TypeKind Nullable::Type() const { return TypeKind::Nullable; }

    const std::string& Nullable::FullName() const { return genericSignature; }

    void Nullable::BindGlobal()
    {
        characteristics[0] = new BuiltInProperty("IsNull", Describer::Public, Boolean::Instance(), true, std::format("call instance bool valuetype {}::get_HasValue()", genericSignature), false, "");
        characteristics[1] = new BuiltInProperty("Value", Describer::Public, nullableType, true, std::format("call instance !0 valuetype {}::get_Value()", genericSignature), false, "");

        const auto constructor = new BuiltInConstructor(this, std::format("call instance void valuetype {}::.ctor(!0)", genericSignature));
        constructor->PushParameterType(nullableType);
        constructors[0] = { ArgumentHash(constructor), constructor };

        const auto defaultConstructor = new BuiltInConstructor(this, "initobj valuetype {}" + genericSignature);
        constructors[1] = { ArgumentHash(defaultConstructor), defaultConstructor };

        ImplicitValueType::BindGlobal();
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
            if (constructor.first == hash)
                return constructor.second;

        return nullptr;
    }

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
        for (const auto characteristic : characteristics)
            delete characteristic;

        for (const auto constructor: constructors)
            delete constructor.second;
    }
}

