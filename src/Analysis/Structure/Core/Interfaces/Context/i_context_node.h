#ifndef I_CONTEXT_NODE_H
#define I_CONTEXT_NODE_H

#include <string>

#include "../i_node.h"
#include "../i_created.h"
#include "../i_slot_size.h"
#include "../i_read_write.h"

namespace Analysis::Structure::Core::Interfaces
{
    class IContextNode : public virtual INode, public virtual ICreated, public virtual ISlotCount, public virtual IReadWrite
    {
        public:
            [[nodiscard]] virtual uintptr_t Metadata() const = 0;
            [[nodiscard]] virtual std::string CILData() const = 0;

            [[nodiscard]] virtual unsigned long ChildCount() const = 0;
            [[nodiscard]] virtual const IContextNode* GetChild(int index) const = 0;
    };
}

#endif
