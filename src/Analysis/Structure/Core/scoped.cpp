#include "scoped.h"

#include "../Local/Scopes/scope.h"

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Local;

namespace Analysis::Structure::Core
{
    Scoped::Scoped(const ScopeNode* const parseNode) : ConstantCollection(), parseNode(parseNode), argumentCount(0)
    {
        scope = new Local::Scope(ScopeType::Scope, "", this);
    }

    const ScopeNode* Scoped::ParseNode() const { return parseNode; }

    unsigned long Scoped::ArgumentCount() const { return argumentCount; }
    unsigned long Scoped::VariableCount() const { return children.size(); }

    Scope* Scoped::Scope() const { return scope; }

    void Scoped::AddArgument(const LocalVariable* parameter)
    {
        argumentCount++;
        AddChild(parameter);
    }

    void Scoped::AddLocalVariable(const LocalVariable* variable)
    {
        AddChild(variable);
    }

    std::optional<unsigned long> Scoped::GetArgumentIndex(const std::string& name) const
    {
        for (int i = 0; i < argumentCount; i++)
            if (children.at(i)->Name() == name)
                return i;

        return std::nullopt;
    }

    const LocalVariable* Scoped::VariableAt(const unsigned long i) const
    {
        return children.at(i);
    }
}
