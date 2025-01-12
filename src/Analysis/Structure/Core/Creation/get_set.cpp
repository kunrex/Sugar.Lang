#include "get_set.h"

using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Core
{
    GetSet::GetSet(Creation::Get* get, Creation::Set* set) : Get(get), Setable(set)
    { }

    bool GetSet::Readable() const { return true; }
    bool GetSet::Writable() const { return true; }
}
