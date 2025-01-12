#ifndef CONSTANT_H
#define CONSTANT_H

#include "../token.h"

namespace Tokens
{
    class Constant final
    {
        private:
            Constant();

        public:
            static Token Null(unsigned long i);

            static Token True(unsigned long i);
            static Token False(unsigned long i);

            static Token Character(unsigned long i, long value);

            static Token Short(unsigned long i, long value);
            static Token Int(unsigned long i, long value);
            static Token Long(unsigned long i, long value);

            static Token Float(unsigned long i, double value);
            static Token Double(unsigned long i, double value);

            static Token String(unsigned long i, std::string value);
    };
}

#endif
