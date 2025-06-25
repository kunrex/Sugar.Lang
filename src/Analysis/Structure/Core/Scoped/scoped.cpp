#include "scoped.h"

#include "../../Local/Scopes/scope.h"

using namespace ParseNodes::Core::Interfaces;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Local;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Core
{
    Scoped::Scoped(const IParseNode* const parseNode) : parseNode(parseNode), parameterCount(0), scope(new Local::Scope(ScopeType::Scope, "", this))
    { }

    Scope* Scoped::Scope() const { return scope; }

    unsigned long Scoped::ParameterCount() const { return parameterCount; }

    const IDataType* Scoped::ParameterAt(const unsigned long index) const
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

    std::pair<const LocalVariable*, unsigned long> Scoped::TryGetGeneratedVariable(const IDataType* const type)
    {
        for (const auto index: generatedIndexes)
            if (index.first == type)
                return { children[index.second], index.second };

        generatedIndexes.emplace_back(type, children.size());
        const auto variable = new LocalVariable(std::format("V_{}", children.size()), Describer::None, type);

        children.push_back(variable);
        return { variable, children.size() - 1 };
    }

    Scoped::~Scoped()
    {
        delete scope;
    }
}
