#ifndef CREATED_H
#define CREATED_H

#include "DataTypes/data_type.h"
#include "Interfaces/i_created.h"

namespace Analysis::Structure::Core
{
    class Created : public virtual Interfaces::ICreated
    {
        protected:
            const Interfaces::IDataType* creationType;

            explicit Created(const Interfaces::IDataType* creationType);

        public:
            [[nodiscard]] const Interfaces::IDataType* CreationType() const override;
    };
}

#endif
