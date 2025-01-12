#include "setable.h"

using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Core
{
    Setable::Setable(Creation::Set* set) : set(set)
    { }

    const Set* Setable::Set() const { return set; }

    bool Setable::Readable() const { return false; }
    bool Setable::Writable() const { return true; }

    Setable::~Setable()
    {
        delete set;
    }
}

