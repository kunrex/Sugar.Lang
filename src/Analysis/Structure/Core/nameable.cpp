#include "nameable.h"

namespace Analysis::Structure::Core
{
    Nameable::Nameable(std::string name) : name(std::move(name))
    { }

    const std::string& Nameable::Name() const { return name; }
}
