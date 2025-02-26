#include "func.h"

#include <map>
#include <format>

#include "generic_extensions.h"
#include "../../DataTypes/data_type_extensions.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

constexpr std::string cil_func = "[System.Runtime]System.Func";

namespace Analysis::Structure::Wrappers
{
    Func::Func() : Class(cil_func, Describer::Public), SingletonCollection(), GenericType(), callSignature(), types()
    { }

    const Func* Func::Instance(const std::vector<const IDataType*>& types)
    {
        static std::map<unsigned long, const Func*> map;

        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto func = new Func();
        for (const auto type : types)
            func->types.push_back(type);

        func->genericSignature = std::format("{}`{}<{}>", cil_func, types.size(), MapGenericSignature(types));
        func->callSignature = MapGenericCallSignature(types);

        func->InitialiseMembers();

        map[hash] = func;
        return func;
    }

    const std::string& Func::FullName() const { return genericSignature; }

    void Func::InitialiseMembers()
    { }
}