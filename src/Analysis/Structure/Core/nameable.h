#ifndef NAMEABLE_H
#define NAMEABLE_H

#include "Interfaces/i_fully_nameable.h"

namespace Analysis::Structure::Core
{
    class Nameable : public virtual IFullyNameable
    {
        protected:
            const std::string name;

            explicit Nameable(std::string name);

        public:
            [[nodiscard]] const std::string& Name() const;
    };
}

#endif