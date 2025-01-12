#ifndef INVOKE_NODE_H
#define INVOKE_NODE_H

#include "base_function_call_node.h"

namespace ParseNodes::Functions::Calling
{
    class InvokeNode final : public BaseFunctionCallNode
    {
        public:
            explicit InvokeNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
