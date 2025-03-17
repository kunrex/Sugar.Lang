#ifndef TYPE_KIND_H
#define TYPE_KIND_H

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
        Referenced = -3
    };
}

#endif
