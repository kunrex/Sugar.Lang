#ifndef I_COLLECTION_TYPE_H
#define I_COLLECTION_TYPE_H

#include "i_data_type.h"

namespace Analysis::Structure::Core::Interfaces
{
    class ICollectionType : public virtual IDataType
    {
        public:
            [[nodiscard]] virtual const IDataType* GenericType() const = 0;
    };
}

#endif
