#ifndef I_TRANSPILABLE_H
#define I_TRANSPILABLE_H

#include "../../../../Services/string_builder.h"

namespace Analysis::Structure::Core::Interfaces
{
    class ITranspilable
    {
        public:
            virtual void Transpile(Services::StringBuilder& builder) const = 0;

            virtual ~ITranspilable() = default;
    };
}

#endif
