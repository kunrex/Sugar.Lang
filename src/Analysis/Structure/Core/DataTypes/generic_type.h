#ifndef GENERIC_TYPE_H
#define GENERIC_TYPE_H

#include <string>

namespace Analysis::Structure::Core
{
    class GenericType
    {
        protected:
            mutable std::string genericSignature;

            GenericType();
    };
}


#endif
