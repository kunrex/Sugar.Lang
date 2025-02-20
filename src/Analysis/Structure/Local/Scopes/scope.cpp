#include "scope.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Local
{
    Scope::Scope(const ScopeType type, const string& name, Scoped* const scoped) : LocalNode(), Nameable(name), ConstantChild(), ConstantCollection(), type(type), scoped(scoped), nested(), variableIndices()
    { }

    MemberType Scope::MemberType() const { return MemberType::Scope; }

    const string& Scope::FullName() const { return name; }

    ScopeType Scope::Type() const { return type; }

    void Scope::AddVariable(const LocalVariable* variable)
    {
        variableIndices[variable->Name()] = scoped->VariableCount();
        scoped->AddLocalVariable(variable);
    }

    std::optional<unsigned long> Scope::GetVariable(const std::string& name) const
    {
        if (variableIndices.contains(name))
            return variableIndices.at(name);

        return parent ? parent->GetVariable(name) : std::nullopt;
    }

    void Scope::AddNested(Scope* const scope)
    {
        nested.push_back(scope);
        scope->SetParent(this);
    }

    unsigned long Scope::NestedCount() const
    {
        return nested.size();
    }

    const Scope* Scope::NestedAt(const unsigned long index) const
    {
        if (index < nested.size())
            return nested.at(index);

        return nullptr;
    }

    Scope::~Scope()
    {
        for (const auto nestedScope: nested)
            delete nestedScope;
    }
}
