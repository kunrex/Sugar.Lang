#include "indexed_context_node.h"

using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    IndexedContextNode::IndexedContextNode(const Variable* variable, const int index) : VariableContext(variable), index(index)
    { }

    int IndexedContextNode::SlotCount() const { return 1;}

    int IndexedContextNode::Index() const { return index; }
}

