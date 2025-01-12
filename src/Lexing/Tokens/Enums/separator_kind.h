#ifndef SEPARATOR_KIND_H
#define SEPARATOR_KIND_H

#include <iostream>

namespace Tokens::Enums
{
    enum class SeparatorKind : short
    {
        Any = 0,
        Dot = 1,
        Comma = 2,

        Colon = 4,
        Semicolon = 8,

        QuestionMark = 16,

        OpenBracket = 32,
        CloseBracket = 64,

        BoxOpenBracket = 128,
        BoxCloseBracket = 256,

        FlowerOpenBracket = 512,
        FlowerCloseBracket = 1024,

        None = 2048
    };

    SeparatorKind operator|(const SeparatorKind& lhs, const SeparatorKind& rhs);
    SeparatorKind operator&(const SeparatorKind& lhs, const SeparatorKind& rhs);

    std::string ToString(const SeparatorKind& separatorKind);
    std::ostream& operator << (std::ostream& os, const SeparatorKind& dt);
}

#endif
