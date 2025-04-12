#ifndef TYPE_KIND_H
#define TYPE_KIND_H

#include "string"

namespace Tokens::Enums
{
    enum class TypeKind : short
    {
        Short = 33,
        Int,
        Long,

        Float,
        Double,

        Boolean,
        Character,

        Array,
        List,
        Dictionary,
        Tuple,

        Func,
        Action,

        Nullable,

        Math,
        String,
        Exception,

        Object,

        Void = -1,
        Custom = -2,
        EnumField = -3,
        Referenced = -4,
    };

    std::string ToString(const TypeKind& kind);
}

#endif
