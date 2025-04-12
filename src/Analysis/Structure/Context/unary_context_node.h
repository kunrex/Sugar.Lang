#ifndef UNARY_CONTEXT_NODE_H
#define UNARY_CONTEXT_NODE_H

#include "context_node.h"

namespace Analysis::Structure::Context
{
    class UnaryContextNode : public FixedContextCollection<1>
    {
        protected:
            UnaryContextNode(const Core::Interfaces::IDataType* creationType, const IContextNode* operand);
    };
}

#endif
