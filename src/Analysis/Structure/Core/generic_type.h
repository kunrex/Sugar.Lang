#ifndef GENERIC_CLASS_H
#define GENERIC_CLASS_H

#include <string>

#include "Interfaces/i_fully_nameable.h"

namespace Analysis::Structure::Core
{
    class GenericType : public virtual IFullyNameable
    {
        protected:
            mutable std::string genericSignature;

            GenericType();
    };
}

#endif
