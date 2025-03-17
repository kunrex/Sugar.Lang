#ifndef KEYWORD_TYPE_H
#define KEYWORD_TYPE_H

namespace Tokens::Enums
{
    enum class KeywordType : short
    {
        Type,
        Loop,
        Control,
        General,
        DataType,
        Function,
        Describer,
        Condition,
    };
}

#endif
