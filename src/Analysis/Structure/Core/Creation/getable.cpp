#include "getable.h"

using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Core
{
    Getable::Getable(Creation::Get* const get) : get(get)
    { }

    const Get* Getable::Get() const { return get; }

    bool Getable::Readable() const { return  true; }
    bool Getable::Writable() const { return  false; }

    Getable::~Getable()
    {
        delete get;
    }
}
