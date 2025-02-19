#include "indexed_context_node.h"

using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Context
{
    IndexedContextNode::IndexedContextNode(const Characteristic* characteristic, const int index) : VariableContext(characteristic), index(index)
    {
        slotCount = 1;
    }

    int IndexedContextNode::Index() const { return index; }
}

