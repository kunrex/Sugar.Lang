#ifndef INPUT_NODE_H
#define INPUT_NODE_H

#include "base_function_call_node.h"

namespace ParseNodes::Functions::Calling
{
    class InputNode final : public BaseFunctionCallNode
    {
        public:
            explicit InputNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
