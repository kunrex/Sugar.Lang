#ifndef BINARY_CONTEXT_NODE_H
#define BINARY_CONTEXT_NODE_H

#include "context_node.h"

namespace Analysis::Structure::Context
{
    class BinaryContextNode : public ContextNode
    {
        protected:
            const ContextNode* lhs;
            const ContextNode* rhs;

            BinaryContextNode(const Core::DataType* creationType, const ContextNode* lhs, const ContextNode* rhs);

        public:
            [[nodiscard]] const ContextNode* LHS() const;
            [[nodiscard]] const ContextNode* RHS() const;

            ~BinaryContextNode() override;
    };
}

#endif
