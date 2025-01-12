#include "accessor.h"

namespace Analysis::Structure::Creation
{
    Accessor::Accessor(const Enums::Describer describer, const ParseNodes::ParseNode* body) : Describable(describer), Scoped(body)
    { }
}
