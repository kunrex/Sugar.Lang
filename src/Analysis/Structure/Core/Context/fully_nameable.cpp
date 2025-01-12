#include "fully_nameable.h"

namespace Analysis::Structure::Core
{
    FullyNameable::FullyNameable() = default;

    std::string FullyNameable::FullName() const { return fullName; }
}
