#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <iostream>

namespace Tokens::Enums
{
    enum class TokenType : short
    {
        Keyword = 1,
        Constant = 2,
        Separator = 4,
        Identifier = 8,

        UnaryOperator = 16,
        BinaryOperator = 32,
        AssignmentOperator = 64,

        Invalid = 128,
        Operator = UnaryOperator | BinaryOperator | AssignmentOperator
    };

    TokenType operator | (const TokenType& lhs, const TokenType& rhs);
    TokenType operator & (const TokenType& lhs, const TokenType& rhs);

    std::string ToString(const TokenType& tokenType);
    std::ostream& operator << (std::ostream& os, const TokenType& dt);
}

#endif
