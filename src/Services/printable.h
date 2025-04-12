#ifndef PRINTABLE_H
#define PRINTABLE_H

#include <string>

namespace Services
{
    class Printable
    {
        public:
            virtual void Print() const;
            virtual void Print(const std::string& indent, bool last) const;

            virtual ~Printable() = default;
    };
}

#endif
