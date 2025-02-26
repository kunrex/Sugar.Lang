#include "tuple.h"

#include <format>

#include "generic_extensions.h"

#include <map>

#include "../../DataTypes/data_type_extensions.h"
#include "../../Global/BuiltIn/built_in_constructor.h"

#include "../../Global/BuiltIn/built_in_property.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;

constexpr std::string cil_tuple = "[System.Runtime]System.Tuple";

namespace Analysis::Structure::Wrappers
{
    Tuple::Tuple() : Class("Tuple", Describer::Public), SingletonCollection(), GenericType(), callSignature(), types()
    { }

    const Tuple* Tuple::Instance(const std::vector<const IDataType*>& types)
    {
        static std::map<unsigned long, const Tuple*> map;

        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto tuple = new Tuple();
        for (const auto type : types)
            tuple->types.push_back(type);

        tuple->genericSignature = std::format("{}`{}<{}>", cil_tuple, types.size(), MapGenericSignature(types));
        tuple->callSignature = MapGenericCallSignature(types);

        tuple->InitialiseMembers();

        map[hash] = tuple;
        return tuple;
    }

    const std::string& Tuple::FullName() const { return genericSignature; }

    void Tuple::InitialiseMembers()
    {
        const auto constructor = new BuiltInConstructor(this, std::format("call instance void class {}::.ctor({})", genericSignature, callSignature));

        int i = 1;
        for (const auto type: types)
        {
            const auto getInstruction = std::format("call instance {} class {}::get_Item{}()", type->FullName(), genericSignature, i);
            PushCharacteristic(new BuiltInProperty(Describer::Public, std::format("Element{}", i++), type, true, getInstruction, false, ""));

            constructor->PushParameterType(type);
        }

        PushConstructor(constructor);
    }
}
