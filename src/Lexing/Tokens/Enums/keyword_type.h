#ifndef KEYWORD_TYPE_H
#define KEYWORD_TYPE_H

namespace Tokens::Enums
{
    enum class KeywordType : short
    {
        General = 0,
        Type = 1,
        Loop = 2,
        DataType = 3,
        Function = 4,
        Describer = 5,
        Condition = 6,
        Control = 7,
    };
}

#endif
