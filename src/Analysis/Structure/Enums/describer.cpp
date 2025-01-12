#include "describer.h"

namespace Analysis::Structure::Enums
{
    Describer operator&(const Describer lhs, const Describer rhs)
    {
        return static_cast<Describer>(static_cast<short>(lhs) & static_cast<short>(rhs));
    }

    Describer operator|(const Describer lhs, const Describer rhs)
    {
        return static_cast<Describer>(static_cast<short>(lhs) | static_cast<short>(rhs));
    }
}