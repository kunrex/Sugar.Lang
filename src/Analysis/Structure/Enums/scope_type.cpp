#include "scope_type.h"

namespace Analysis::Structure::Enums
{
    ScopeType operator&(const ScopeType& lhs, const ScopeType& rhs)
    {
        return static_cast<ScopeType>(static_cast<short>(lhs) & static_cast<short>(rhs));
    }

    ScopeType operator|(const ScopeType& lhs, const ScopeType& rhs)
    {
        return static_cast<ScopeType>(static_cast<short>(lhs) | static_cast<short>(rhs));
    }
}