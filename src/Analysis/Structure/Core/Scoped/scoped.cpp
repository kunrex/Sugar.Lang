#include "scoped.h"

#include "../../Local/Scopes/scope.h"

using namespace ParseNodes;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Local;

namespace Analysis::Structure::Core
{
    Scoped::Scoped(const NodeCollection<ParseNodes::ParseNode>* const parseNode) : ConstantCollection(), parseNode(parseNode), parameterCount(0), scope(new Local::Scope(ScopeType::Scope, "", this))
    { }

    S

    const NodeCollection<ParseNode>* Scoped::ParseNode() const { return parseNode; }

    Scope* Scoped::Scope() const { return scope; }

    unsigned long Scoped::ParameterCount() const { return parameterCount; }

    const Interfaces::IDataType* Scoped::ParameterAt(const unsigned long index) const
    {
        return children.at(index)->CreationType();
    }

    unsigned long Scoped::VariableCount() const { return children.size(); }

    const LocalVariable* Scoped::VariableAt(const unsigned long i) const
    {
        return children.at(i);
    }

    void Scoped::AddParameter(const LocalVariable* parameter)
    {
        parameterCount++;
        AddChild(parameter);
    }

    void Scoped::AddLocalVariable(const LocalVariable* variable)
    {
        AddChild(variable);
    }

    std::optional<unsigned long> Scoped::GetParameterIndex(const std::string& name) const
    {
        for (int i = 0; i < parameterCount; i++)
            if (children.at(i)->Name() == name)
                return i;

        return std::nullopt;
    }
}
