#ifndef CHILD_CODE_H
#define CHILD_CODE_H

namespace ParseNodes::Enums
{
    enum class ChildCode : short
    {
        Describer,
        Type,
        Identifier,

        Parameters,

        Body,
        Expression,

        Get,
        Set,

        Pre,
        Post,

        LHS,
        RHS,
    };
}

#endif