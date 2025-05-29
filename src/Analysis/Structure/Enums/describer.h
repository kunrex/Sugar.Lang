#ifndef DESCRIBER_H
#define DESCRIBER_H

#include <string>

#include "../../../Parsing/ParseNodes/Core/Interfaces/i_parse_node.h"

namespace Analysis::Structure::Enums
{
    enum class Describer : short
    {
        None = 0,

        Ref = 1,

        Public = 2,
        Private = 4,

        Static = 8,

        Const = 16,
        Constexpr = 32 | Static,

        Entrypoint = Public | Static | 64,

        AccessModifiers = Public | Private,

        PublicStatic = Public | Static,

        ValidEnum = AccessModifiers,
        ValidStruct = AccessModifiers,
        ValidClass = AccessModifiers | Static,
    };

    Describer operator & (const Describer& lhs, const Describer& rhs);
    Describer operator | (const Describer& lhs, const Describer& rhs);

    Describer FromNode(const ParseNodes::Core::Interfaces::IParseNode* node);

    std::string ToString(const Describer& describer);
}

#endif
