#include "scoped.h"

namespace Analysis::Structure::Core
{
    Scoped::Scoped(const ParseNodes::ParseNode* parseNode) : scope(), parseNode(parseNode)
    { }
}
