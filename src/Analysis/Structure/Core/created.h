#ifndef CREATED_H
#define CREATED_H

#include "Interfaces/i_created.h"

#include "../source_object.h"

namespace Analysis::Structure::Core
{
    class Created : public virtual Interfaces::ICreated
    {
        protected:
            const DataType* creationType;

            explicit Created(const DataType* creationType);

        public:
            [[nodiscard]] const DataType* CreationType() const override;
    };
}

#endif
