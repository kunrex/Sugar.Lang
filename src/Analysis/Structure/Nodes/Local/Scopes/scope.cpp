#include "scope.h"

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Local
{
    Scope::Scope(const ScopeType type, const std::string& name, Core::Scoped* const scoped) : LocalNode(), FullyNameable(), ConstantChild(), ConstantCollection(), type(type), scoped(scoped), nested(), variableIndices()
    {
        fullName = name;
    }

    MemberType Scope::MemberType() const { return MemberType::Scope; }

    ScopeType Scope::Type() const { return type; }

    void Scope::AddVariable(const LocalVariable* variable)
    {
        variableIndices[variable->Name()] = scoped->VariableCount();
        scoped->AddLocalVariable(variable);
    }

    int Scope::GetVariable(const std::string& name) const
    {
        if (variableIndices.contains(name))
            return variableIndices.at(name);

        return parent ? parent->GetVariable(name) : -1;
    }

    void Scope::AddNested(Scope* const scope)
    {
        nested.push_back(scope);
        scope->SetParent(this);
    }

    int Scope::NestedCount() const
    {
        return nested.size();
    }

    const Scope* Scope::NestedAt(const int index) const
    {
        if (index >= 0 && index < nested.size())
            return nested.at(index);

        return nullptr;
    }

    const std::string& Scope::FullName() const { return fullName; }

    Scope::~Scope()
    {
        for (const auto nestedScope: nested)
            delete nestedScope;
    }
}
