#include "action.h"

#include <map>
#include <format>

#include "generic_extensions.h"

#include "../Value/boolean.h"

#include "../../DataTypes/data_type_extensions.h"
#include "../../Global/Functions/operator_overload.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Global;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

const string cil_action = "[System.Runtime]System.Action";

namespace Analysis::Structure::Wrappers
{
    Action::Action() : ImplicitClass(cil_action, Describer::Public), SingletonService()
    { }

    const Action* Action::Instance(const std::vector<const IDataType*>& types)
    {
        static std::map<unsigned long, const Action*> map;

        const auto hash = ArgumentHash(types);

        if (map.contains(hash))
            return map.at(hash);

        const auto action = new Action();
        for (const auto type : types)
            action->types.push_back(type);

        if (types.empty())
            action->genericSignature = cil_action;
        else
            action->genericSignature = std::format("{}`{}<{}>", cil_action, types.size(), MapGenericSignature(types));

        action->BindGlobal();

        map[hash] = action;
        return action;
    }

    TypeKind Action::Type() const { return TypeKind::Action; }

    const std::string& Action::FullName() const { return genericSignature; }

    unsigned long Action::TypeCount() const { return types.size(); }

    const IDataType* Action::TypeAt(const unsigned long index) const { return types.at(index); }

    const std::string& Action::DelegateSignature() const { return genericSignature; }

    void Action::BindGlobal()
    {
        const auto equals = new GeneratedOverload(SyntaxKind::Equals, Boolean::Instance(), "call bool [System.Runtime]System.Delegate::op_Equality(class [System.Runtime]System.Delegate, class [System.Runtime]System.Delegate)");
        equals->PushParameterType(this);
        equals->PushParameterType(this);
        overloads[0] = { SyntaxKind::Equals, equals };

        const auto notEquals = new GeneratedOverload(SyntaxKind::NotEquals, Boolean::Instance(), "call bool [System.Runtime]System.Delegate::op_Equality(class [System.Runtime]System.Delegate, class [System.Runtime]System.Delegate) ldc.i4.0 ceq");
        notEquals->PushParameterType(this);
        notEquals->PushParameterType(this);
        overloads[1] = { SyntaxKind::NotEquals, notEquals };
    }

    const ICharacteristic* Action::FindCharacteristic(const std::string& name) const
    { return nullptr; }

    const IConstructor* Action::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Action::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IOperatorOverload* Action::FindOverload(const SyntaxKind base) const
    {
        for (const auto overload: overloads)
            if (overload.first == base)
                return overload.second;

        return nullptr;
    }

    Action::~Action()
    {
        for (const auto overload : overloads)
            delete overload.second;
    }
}