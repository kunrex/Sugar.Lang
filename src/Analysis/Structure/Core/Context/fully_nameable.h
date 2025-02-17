#ifndef FULLY_NAMEABLE_H
#define FULLY_NAMEABLE_H

#include <string>

namespace Analysis::Structure::Core
{
    class FullyNameable
    {
        protected:
            mutable std::string fullName;

            FullyNameable();

        public:
            [[nodiscard]] virtual const std::string& FullName() const = 0;
            virtual ~FullyNameable() = 0;
    };
}

#endif
