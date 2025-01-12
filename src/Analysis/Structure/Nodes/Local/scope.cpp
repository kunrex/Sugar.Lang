#include "scope.h"

namespace Analysis::Structure::Local
{
    Enums::MemberType Scope::MemberType() const { return Enums::MemberType::StaticMethodCall; }
}
