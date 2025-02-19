#include "action.h"

#include <map>
#include <format>

#include "generic_extensions.h"

using namespace std;

using namespace Analysis::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string cil_action = "[System.Runtime]System.Action";

namespace Analysis::Structure::Wrappers
{
    Action::Action() : Class(cil_action, Describer::Public), SingletonCollection(),  types(), genericSignature(), callSignature()
    { }

    const Action* Action::Instance(const std::vector<const DataType*>& types)
    {
        static std::map<string, const Action*> map;
        const auto signature = MapGenericSignature(types);

        if (map.contains(signature))
            return map.at(signature);

        const auto action = new Action();
        for (const auto type : types)
            action->types.push_back(type);

        action->genericSignature = std::format("`{}<{}>", types.size(), signature);
        action->fullName = std::format("{}{}", cil_action, action->genericSignature);

        action->InitialiseMembers();
        map[signature] = action;
        return action;
    }

    const std::string& Action::GenericSignature() const
    {
        return genericSignature;
    }

    const std::string& Action::CallSignature() const
    {
        if (callSignature.empty())
        {
            callSignature = "(";
            for (int i = 0; i < types.size(); i++)
            {
                callSignature += std::format("!{}", i);
                if (i < types.size() - 1)
                    callSignature += " ";
            }

            callSignature += ")";
        }

        return callSignature;
    }

    void Action::InitialiseMembers()
    { }

    unsigned long Action::TypeCount() const {  return types.size(); }

    const Core::DataType* Action::TypeAt(const unsigned long index) const
    {
        if (index >= types.size())
            return nullptr;

        return types.at(index);
    }
}