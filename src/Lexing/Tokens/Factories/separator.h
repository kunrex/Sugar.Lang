#ifndef SEPARATOR_H
#define SEPARATOR_H

#include "../token.h"

namespace Tokens
{
    class Separator final
    {
        private:
            Separator();

            static Token Create(unsigned long i, Enums::SyntaxKind syntaxKind, const std::string& value);

        public:
            static Token Dot(unsigned long i);
            static Token Comma(unsigned long i);

            static Token Colon(unsigned long i);
            static Token Semicolon(unsigned long i);

            static Token QuestionMark(unsigned long i);

            static Token OpenBracket(unsigned long i);
            static Token CloseBracket(unsigned long i);

            static Token BoxOpenBracket(unsigned long i);
            static Token BoxCloseBracket(unsigned long i);

            static Token FlowerOpenBracket(unsigned long i);
            static Token FlowerCloseBracket(unsigned long i);
    };
}

#endif
