#include "tuple.h"

#include <format>

#include "generic_extensions.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

constexpr std::string_view tuple_cil = "[System.ValueTuple]System.ValueTuple";

namespace Analysis::Structure::Wrappers
{
    Tuple::Tuple() : Class("Tuple", Describer::Public), SingletonCollection(), types(), genericSignature()
    { }

    void Tuple::PushType(const DataType* type)
    {
        if (types.size() < max_tuple_length - 1)
            types.push_back(type);
    }

    const Tuple* Tuple::Instance(const std::vector<const DataType*>& types)
    {
        static std::map<string, const Tuple*> map;
        const auto signature = MapGenericSignature(types);

        if (map.contains(signature))
            return map.at(signature);

        const auto tuple = new Tuple();
        for (const auto type : types)
            tuple->PushType(type);

        tuple->InitialiseMembers();
        map[signature] = tuple;

        tuple->fullName = std::format("{}{}", tuple_cil, tuple->genericSignature);
        return tuple;
    }

    const std::string& Tuple::GenericSignature() const
    {
        if (genericSignature.empty())
            genericSignature = std::format("`{}<{}>", types.size(), MapGenericSignature(types));

        return genericSignature;
    }

    void Tuple::InitialiseMembers()
    {

    }
}
