#include "func.h"

#include <map>
#include <format>

#include "generic_extensions.h"

using namespace std;

using namespace Analysis::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;

constexpr std::string_view action_cil = "[mscorlib]System.Func";

namespace Analysis::Structure::Wrappers
{
    Func::Func(const MethodFunction* definition) : Class("Func", Describer::Public), SingletonCollection(), genericSignature(), callSignature()
    { }

    const Func* Func::Instance(const std::vector<const DataType*>& types)
    {
        static std::map<string, const Func*> map;
        const auto signature = MapGenericSignature(types);

        if (map.contains(signature))
            return map.at(signature);

        const auto action = new Func();
        for (const auto type : types)
            action->types.push_back(type);

        action->genericSignature = std::format("`{}<{}>", types.size(), signature);
        action->fullName = std::format("{}{}", action_cil, action->genericSignature);

        action->InitialiseMembers();
        map[signature] = action;
        return action;
    }

    const std::string& Func::GenericSignature() const
    {
        return genericSignature;
    }

    const std::string& Func::CallSignature() const
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

    void Func::InitialiseMembers()
    {

    }
}