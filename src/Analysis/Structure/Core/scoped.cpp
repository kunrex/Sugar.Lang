#include "scoped.h"

#include "../../../Analysis/Structure/Nodes/Local/Scopes/scope.h"

using namespace ParseNodes;
using namespace ParseNodes::Groups;

using namespace Analysis::Structure::Local;

namespace Analysis::Structure::Core
{
    Scoped::Scoped(const ScopeNode* parseNode) : ConstantCollection(), parseNode(parseNode), argumentCount(0)
    {
        scope = new Scope(this);
    }

    const ScopeNode* Scoped::ParseNode() const { return parseNode; }

    int Scoped::ArgumentCount() const { return argumentCount; }
    int Scoped::VariableCount() const { return children.size(); }

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

    bool Scoped::ContainsArgument(const std::string& name) const
    {
        return GetArgument(name) != nullptr;
    }

    int Scoped::GetArgument(const std::string& name) const
    {
        for (int i = 0; i < argumentCount; i++)
            if (children.at(i)->Name() == name)
                return i;

        return -1;
    }

    const LocalVariable* Scoped::VariableAt(const int i) const
    {
        return children.at(i);
    }
}
