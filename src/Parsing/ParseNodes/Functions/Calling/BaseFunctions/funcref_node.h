#ifndef FUNCREF_NODE_H
#define FUNCREF_NODE_H

#include "base_function_call_node.h"

namespace ParseNodes::Functions::Calling
{
    class FuncRefNode final : public BaseFunctionCallNode
    {
        public:
            explicit FuncRefNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
