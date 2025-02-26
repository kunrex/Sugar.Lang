#ifndef REF_CALL_NODE_H
#define REF_CALL_NODE_H

#include "base_function_call_node.h"

namespace ParseNodes::Functions::Calling
{
    class RefCallNode final : public BaseFunctionCallNode
    {
        public:
            explicit RefCallNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
