#ifndef FORMAT_NODE_H
#define FORMAT_NODE_H

#include "base_function_call_node.h"

namespace ParseNodes::Functions::Calling
{
    class FormatNode final : public BaseFunctionCallNode
    {
        public:
            explicit FormatNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
