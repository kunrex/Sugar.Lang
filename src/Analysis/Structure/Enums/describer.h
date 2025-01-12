#ifndef DESCRIBER_H
#define DESCRIBER_H

namespace Analysis::Structure::Enums
{
    enum class Describer : short
    {
        Ref = 1,

        Const = 2,

        Public = 4,
        Private = 8,

        Static = 16,

        AccessModifiers = Public | Private,

        PublicStatic = Public | Static,

        FunctionOnly = AccessModifiers | Static,
        All = AccessModifiers | Static | Const | Ref,
    };

    Describer operator & (Describer lhs, Describer rhs);
    Describer operator | (Describer lhs, Describer rhs);
}

#endif
