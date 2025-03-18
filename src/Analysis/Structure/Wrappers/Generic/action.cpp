#include "action.h"

#include <map>
#include <format>

#include "generic_extensions.h"
#include "../../DataTypes/data_type_extensions.h"

using namespace std;

using namespace Tokens::Enums;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::DataTypes;
using namespace Analysis::Structure::Core::Interfaces;

constexpr std::string cil_action = "[System.Runtime]System.Action";

namespace Analysis::Structure::Wrappers
{
    Action::Action() : BuiltInClass(cil_action, Describer::Public), SingletonCollection(), genericSignature(), types()
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

        action->InitializeMembers();

        map[hash] = action;
        return action;
    }

    TypeKind Action::Type() const { return TypeKind::Action; }

    const std::string& Action::FullName() const { return genericSignature; }

    unsigned long Action::TypeCount() const { return types.size(); }

    const IDataType* Action::TypeAt(const unsigned long index) const { return types.at(index); }

    const std::string& Action::DelegateSignature() const { return genericSignature; }

    void Action::InitializeMembers()
    { }

    const ICharacteristic* Action::FindCharacteristic(const std::string& name) const
    { return nullptr; }

    const IFunction* Action::FindConstructor(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunctionDefinition* Action::FindFunction(const std::string& name, const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IIndexerDefinition* Action::FindIndexer(const std::vector<const IDataType*>& argumentList) const
    { return nullptr; }

    const IFunction* Action::FindImplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IFunction* Action::FindExplicitCast(const IDataType* returnType, const IDataType* fromType) const
    { return nullptr; }

    const IOperatorOverload* Action::FindOverload(const SyntaxKind base) const
    { return nullptr; }
}