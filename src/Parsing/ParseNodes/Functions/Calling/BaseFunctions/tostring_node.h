#ifndef TOSTRING_NODE_H
#define TOSTRING_NODE_H

#include "base_function_call_node.h"

namespace ParseNodes::Functions::Calling
{
    class ToStringNode final : public BaseFunctionCallNode
    {
        public:
            explicit ToStringNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
