#include "nullable.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Enums;

constexpr std::string_view nullable_cil = "[mscorlib]System.Nullable";

namespace Analysis::Structure::Wrappers
{
    Nullable::Nullable(const DataType* nullableType) : Class("NullableType", Describer::Public), nullableType(nullableType), genericSignature()
    { }

    const Nullable* Nullable::Instance(const DataType* dataType)
    {
        static std::map<string, const Nullable*> map;

        if (map.contains(dataType->FullName()))
            return map[dataType->FullName()];

        const auto nullable = new Nullable(dataType);
        map[dataType->FullName()] = nullable;

        nullable->fullName = std::format("{}{}", nullable_cil, nullable->genericSignature);
        return nullable;
    }

    const std::string& Nullable::GenericSignature() const
    {
        if (genericSignature.empty())
            genericSignature = std::format("`1<{}>", nullableType->FullName());

        return genericSignature;
    }


    void Nullable::InitialiseMembers()
    {

    }
}

