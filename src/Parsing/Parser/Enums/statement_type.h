#ifndef STATEMENT_TYPE_H
#define STATEMENT_TYPE_H

namespace Parsing::Enums
{
    enum class StatementType : short
    {
        Import = 1,

        Declaration = 2,

        Expression = 4,

        Control = 8,

        Loop = 16,
        Condition = 32,

        ClassDefinition = 64,
        FunctionDefinition = 128,

        Scope = 256,

        Empty = 512,

        Standalone = Import | Expression | Loop | Condition | Scope | Control,

        Any = Import | Declaration | Expression | Control | ClassDefinition | FunctionDefinition | Loop | Condition | ClassDefinition | FunctionDefinition | Scope | Empty,
    };

    StatementType operator&(const StatementType& lhs, const StatementType& rhs);
    StatementType operator|(const StatementType& lhs, const StatementType& rhs);
}

#endif
