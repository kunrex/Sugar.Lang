#ifndef CONTEXT_NODE_H
#define CONTEXT_NODE_H

#include <string>

#include "../Core/created.h"
#include "../Core/Interfaces/Context/i_context_node.h"

namespace Analysis::Structure::Context
{
    class ContextNode : public Core::Created, public virtual Core::Interfaces::IContextNode
    {
        protected:
            explicit ContextNode(const Core::Interfaces::IDataType* creationType);

        public:
            [[nodiscard]] virtual std::string CILData() const = 0;
    };
}

#endif
