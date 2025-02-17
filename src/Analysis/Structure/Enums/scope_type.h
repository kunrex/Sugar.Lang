#ifndef SCOPE_TYPE_H
#define SCOPE_TYPE_H

namespace Analysis::Structure::Enums
{
    enum class ScopeType : short
    {
        Scope = 1,

        Condition = 2,

        Loop = 4,
        Increment = 8,

        LoopBody = Loop | Scope,
        LoopCondition = Loop | Condition,

        ConditionScope = Condition | Scope,
    };

    ScopeType operator & (const ScopeType& lhs, const ScopeType& rhs);
    ScopeType operator | (const ScopeType& lhs, const ScopeType& rhs);
}

#endif
