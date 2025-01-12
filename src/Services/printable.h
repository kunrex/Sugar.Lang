#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <iostream>

#include "destructible.h"

namespace Services
{
    class Printable : Destructible
    {
        public:
            virtual void Print() const;
            virtual void Print(std::string indent, bool last) const;
    };
}

#endif
