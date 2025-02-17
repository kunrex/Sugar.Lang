#ifndef DESCRIBER_H
#define DESCRIBER_H

#include "../../../Parsing/ParseNodes/Describers/describer_node.h"

namespace Analysis::Structure::Enums
{
    enum class Describer : short
    {
        Ref = 1,

        Const = 2,

        Public = 4,
        Private = 8,

        Static = 16,

        None = 32,

        PublicStatic = Public | Static,
        AccessModifiers = Public | Private,

        EnumOnly = AccessModifiers,
        StructOnly = AccessModifiers,
        ClassOnly = AccessModifiers | Static,

        FunctionOnly = AccessModifiers | Static,
    };

    Describer operator & (const Describer& lhs, const Describer& rhs);
    Describer operator | (const Describer& lhs, const Describer& rhs);

    Describer FromNode(const ParseNodes::Describers::DescriberNode* node);
}

#endif
