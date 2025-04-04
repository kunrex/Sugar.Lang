#ifndef BINARY_CONTEXT_NODE_H
#define BINARY_CONTEXT_NODE_H

#include "context_node.h"

namespace Analysis::Structure::Context
{
    class BinaryContextNode : public FixedContextCollection<2>
    {
        protected:
            BinaryContextNode(const Core::Interfaces::IDataType* creationType, const IContextNode* lhs, const IContextNode* rhs);
    };
}

#endif
