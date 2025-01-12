#include "nameable.h"

using namespace std;

namespace Analysis::Structure::Core
{
    Nameable::Nameable(std::string name) : FullyNameable(), name(std::move(name))
    { }

    const std::string& Nameable::Name() const { return name; }
}
