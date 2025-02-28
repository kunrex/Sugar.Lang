#ifndef UNARY_CONTEXT_NODE_H
#define UNARY_CONTEXT_NODE_H

#include "context_node.h"

namespace Analysis::Structure::Context
{
    class UnaryContextNode : public ContextNode
    {
        protected:
            const ContextNode* operand;

            UnaryContextNode(const Core::Interfaces::IDataType* creationType, const ContextNode* operand);

        public:
            [[nodiscard]] const ContextNode* Operand() const;

            ~UnaryContextNode() override;
    };
}

#endif
