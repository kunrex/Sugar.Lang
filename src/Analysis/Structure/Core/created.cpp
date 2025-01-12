#include "created.h"

namespace Analysis::Structure::Core
{
    Created::Created(const DataType* creationType) : creationType(creationType)
    { }

    const DataType* Created::CreationType() const { return creationType; }
}
