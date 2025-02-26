#ifndef NAMEABLE_H
#define NAMEABLE_H

#include "Interfaces/i_nameable.h"
#include "Interfaces/i_fully_nameable.h"

namespace Analysis::Structure::Core
{
    class Nameable : public virtual Interfaces::INameable, public virtual Interfaces::IFullyNameable
    {
        protected:
            const std::string name;

            explicit Nameable(std::string name);

        public:
            [[nodiscard]] const std::string& Name() const override;
    };
}

#endif