#include "created.h"

namespace Analysis::Structure::Core
{
    Created::Created(const DataType* const creationType) : creationType(creationType)
    { }

    const DataType* Created::CreationType() const { return creationType; }
}
