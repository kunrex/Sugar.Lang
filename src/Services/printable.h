#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <iostream>

namespace Services
{
    class Printable
    {
        public:
            virtual void Print() const;
            virtual void Print(std::string indent, bool last) const;

            virtual ~Printable() = 0;
    };
}

#endif
