#ifndef DESCRIBER_H
#define DESCRIBER_H

#include "../../../Parsing/ParseNodes/Describers/describer_node.h"

namespace Analysis::Structure::Enums
{
    enum class Describer : short
    {
        None = 0,

        Ref = 1,

        Public = 2,
        Private = 4,

        Static = 8,

        AccessModifiers = Public | Private,

        ValidEnum = AccessModifiers,
        ValidStruct = AccessModifiers,
        ValidClass = AccessModifiers | Static,

        ValidGlobalMember = AccessModifiers | Static,

        ValidFunctionArgument = Ref,

        PublicStatic = Public | Static,
    };

    Describer operator & (const Describer& lhs, const Describer& rhs);
    Describer operator | (const Describer& lhs, const Describer& rhs);

    Describer FromNode(const ParseNodes::Describers::DescriberNode* node);

    std::string ToString(const Describer& describer);
}

#endif
