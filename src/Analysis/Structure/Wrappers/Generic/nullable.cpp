#include "nullable.h"

#include <map>
#include <format>

#include "../../DataTypes/data_type_extensions.h"

#include "../../Global/BuiltIn/built_in_indexer.h"
#include "../../Global/BuiltIn/built_in_property.h"
#include "../../Global/BuiltIn/built_in_constructor.h"

#include "../Value/boolean.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;

constexpr std::string cil_nullable = "[System.Runtime]System.Nullable";

namespace Analysis::Structure::Wrappers
{
    Nullable::Nullable(const DataType* const nullableType) : ValueType(cil_nullable, Describer::Public), nullableType(nullableType)
    {
        slotCount = 0;
    }

    const Nullable* Nullable::Instance(const DataType* const dataType)
    {
        static std::map<unsigned long, const Nullable*> map;

        const std::vector types({ dataType });
        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto nullable = new Nullable(dataType);
        nullable->genericSignature = std::format("{}`1<{}>", cil_nullable, dataType->FullName());

        nullable->InitialiseMembers();

        map[hash] = nullable;
        return nullable;
    }

    int Nullable::SlotCount() const
    {
        if (slotCount == 0)
        {
            const auto alignment = std::min(nullableType->SlotCount(), word_size);
            const auto size = ((1 + (alignment - 1)) & ~(alignment - 1) + nullableType->SlotCount() + (alignment - 1)) & ~(alignment - 1);

            slotCount = (size + (word_size - 1)) / word_size;
        }

        return slotCount;
    }

    const std::string& Nullable::FullName() const {  return genericSignature; }

    void Nullable::InitialiseMembers()
    {
        const auto isNull = std::format("call instance bool valuetype {}::get_HasValue()", genericSignature);
        PushCharacteristic(new BuiltInProperty(Describer::Public, "IsNull", &Boolean::Instance(), true, isNull, false, ""));

        const auto value = std::format("call instance !0 valuetype {}::get_Value()", genericSignature);
        PushCharacteristic(new BuiltInProperty(Describer::Public, "Value", nullableType, true, value, false, ""));

        const auto constructor = new BuiltInConstructor(this, std::format("call instance void valuetype {}::.ctor(!0)", genericSignature));
        constructor->PushParameterType(nullableType);
        PushConstructor(constructor);

        const auto defaultConstructor = new BuiltInConstructor(this, std::format("initobj valuetype {}", genericSignature));
        PushConstructor(defaultConstructor);
    }
}

