#include "created.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Core
{
    Created::Created(const IDataType* const creationType) : creationType(creationType)
    { }

    const IDataType* Created::CreationType() const { return creationType; }
}
