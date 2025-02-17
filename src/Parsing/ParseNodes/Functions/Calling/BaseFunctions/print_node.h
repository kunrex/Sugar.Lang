#ifndef PRINT_NODE_H
#define PRINT_NODE_H

#include "base_function_call_node.h"

namespace ParseNodes::Functions::Calling
{
    class PrintNode final : public BaseFunctionCallNode
    {
        public:
            explicit PrintNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };

    class PrintlnNode final : public BaseFunctionCallNode
    {
        public:
            explicit PrintlnNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
