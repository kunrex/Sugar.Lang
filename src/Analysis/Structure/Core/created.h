#ifndef CREATED_H
#define CREATED_H

#include "../source_object.h"

namespace Analysis::Structure::Core
{
    class Created
    {
        protected:
            const DataType* creationType;

            explicit Created(const DataType* creationType);

        public:
            [[nodiscard]] const DataType* CreationType() const;
    };
}

#endif
