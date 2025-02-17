#include "default_valued.h"

using namespace ParseNodes;

namespace Analysis::Structure::Core
{
    DefaultValued::DefaultValued(const ParseNodes::ParseNode* parseNode) : parseNode(parseNode)
    { }

    const ParseNode* DefaultValued::ParseNode() const { return parseNode; }
}
