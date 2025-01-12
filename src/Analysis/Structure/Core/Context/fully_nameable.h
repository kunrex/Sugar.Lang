#ifndef FULLY_NAMEABLE_H
#define FULLY_NAMEABLE_H

#include <string>

namespace Analysis::Structure::Core
{
    class FullyNameable
    {
        protected:
            std::string fullName;

            FullyNameable();

        public:
            [[nodiscard]] std::string FullName() const;
    };
}

#endif
