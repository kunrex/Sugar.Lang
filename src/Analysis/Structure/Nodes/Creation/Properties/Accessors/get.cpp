#include "get.h"

namespace Analysis::Structure::Creation
{
    Get::Get(const Enums::Describer describer, const ParseNodes::ParseNode* body) : Accessor(describer, body)
    { }
}
