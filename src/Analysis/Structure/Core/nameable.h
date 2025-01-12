#ifndef NAMEABLE_H
#define NAMEABLE_H

#include "Context/fully_nameable.h"

namespace Analysis::Structure::Core
{
    class Nameable : public FullyNameable
    {
        protected:
            const std::string name;

            explicit Nameable(std::string name);

        public:
            [[nodiscard]] const std::string& Name() const;
    };
}

#endif