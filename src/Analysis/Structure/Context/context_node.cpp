#include "context_node.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    ContextNode::ContextNode(const IDataType* const creationType) : Created(creationType)
    { }
}