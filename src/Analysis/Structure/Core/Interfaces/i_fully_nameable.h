#ifndef I_FULLY_NAMEABLE_H
#define I_FULLY_NAMEABLE_H

#include <string>

namespace Analysis::Structure::Core
{
    class IFullyNameable
    {
        public:
            [[nodiscard]] virtual const std::string& FullName() const = 0;

            virtual ~IFullyNameable() = default;
    };
}

#endif
