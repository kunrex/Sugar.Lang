#include "action.h"

#include <map>
#include <format>

#include "generic_extensions.h"
#include "../../DataTypes/data_type_extensions.h"

using namespace std;

using namespace Analysis::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;

constexpr std::string cil_action = "[System.Runtime]System.Action";

namespace Analysis::Structure::Wrappers
{
    Action::Action() : Class(cil_action, Describer::Public), SingletonCollection(), GenericType(), callSignature(), types()
    { }

    const Action* Action::Instance(const std::vector<const DataType*>& types)
    {
        static std::map<unsigned long, const Action*> map;

        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto action = new Action();
        for (const auto type : types)
            action->types.push_back(type);

        if (types.empty())
        {
            action->genericSignature = cil_action;
            action->callSignature = "";
        }
        else
        {
            action->genericSignature = std::format("{}`{}<{}>", cil_action, types.size(), MapGenericSignature(types));
            action->callSignature = MapGenericCallSignature(types);
        }

        action->InitialiseMembers();

        map[hash] = action;
        return action;
    }

    const std::string& Action::FullName() const { return genericSignature; }

    unsigned long Action::TypeCount() const {  return types.size(); }

    const Core::DataType* Action::TypeAt(const unsigned long index) const { return types.at(index); }

    void Action::InitialiseMembers()
    { }
}