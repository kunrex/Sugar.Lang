#ifndef CONTEXT_NODE_H
#define CONTEXT_NODE_H

#include <string>

#include "../../Core/created.h"
#include "../../Core/Interfaces/i_node.h"
#include "../../Core/Interfaces/i_slot_size.h"
#include "../../Core/Interfaces/i_read_write.h"

namespace Analysis::Structure::Context
{
    class ContextNode : public Core::Interfaces::INode, public Core::Created, public Core::Interfaces::ISlotSize, public Core::Interfaces::IReadWrite
    {
        protected:
            explicit ContextNode(const Core::DataType* creationType);

        public:
            [[nodiscard]] virtual std::string InstructionGet() const = 0;
            [[nodiscard]] virtual std::string InstructionSet() const = 0;
    };
}

#endif
