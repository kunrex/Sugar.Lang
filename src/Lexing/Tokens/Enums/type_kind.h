#ifndef TYPE_KIND_H
#define TYPE_KIND_H

#include <iostream>

namespace Tokens::Enums
{
    enum class TypeKind : short
    {
        Short = 97,
        Int = 98,
        Long = 99,

        Float = 100,
        Double = 101,

        Boolean = 102,
        Character = 103,

        String = 104,
        Object = 105,

        Array = 106,
        List = 107,
        Dictionary = 108,
        Tuple = 109,

        Nullable = 110,
        Exception = 111,

        Math = 112
    };

    std::string ToString(const TypeKind& typeKind);
    std::ostream& operator << (std::ostream& os, const TypeKind& dt);
}

#endif
