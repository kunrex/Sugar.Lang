#include "context_node.h"

using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Context
{
    ContextNode::ContextNode(const DataType* creationType) : Created(creationType), slotCount(0)
    { }

    int ContextNode::SlotCount() const { return slotCount; }
}