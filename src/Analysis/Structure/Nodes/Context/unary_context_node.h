#ifndef UNARY_CONTEXT_NODE_H
#define UNARY_CONTEXT_NODE_H

#include "context_node.h"

namespace Analysis::Structure::Context
{
    class UnaryContextNode : public ContextNode
    {
        protected:
            const ContextNode* operand;

            UnaryContextNode(const Core::DataType* creationType, const ContextNode* operand);

        public:
            [[nodiscard]] const ContextNode* Operand() const;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] virtual bool IsPrefix() const = 0;

            ~UnaryContextNode() override;
    };
}

#endif
