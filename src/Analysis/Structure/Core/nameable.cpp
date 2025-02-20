#include "nameable.h"

using namespace std;

namespace Analysis::Structure::Core
{
    Nameable::Nameable(string name) : name(std::move(name))
    { }

    const string& Nameable::Name() const { return name; }
}
