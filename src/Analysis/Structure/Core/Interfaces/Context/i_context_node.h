#ifndef I_CONTEXT_NODE_H
#define I_CONTEXT_NODE_H

#include "../i_node.h"
#include "../i_created.h"
#include "../i_slot_size.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IContextNode : public virtual INode, public virtual ICreated, public virtual ISlotSize, public virtual IReadWrite
    {

    };
}

#endif
