#ifndef I_CREATED_H
#define I_CREATED_H

#include "../../source_object.h"

namespace Analysis::Structure::Core::Interfaces
{
    class ICreated
    {
        public:
            [[nodiscard]] virtual const DataType* CreationType() const = 0;

            virtual ~ICreated() = default;
    };
}

#endif
