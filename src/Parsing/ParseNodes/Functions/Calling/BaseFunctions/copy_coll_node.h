#ifndef COPY_COLL_NODE_H
#define COPY_COLL_NODE_H

#include "base_function_call_node.h"

namespace ParseNodes::Functions::Calling
{
    class CopyCallNode final : public BaseFunctionCallNode
    {
        public:
            explicit CopyCallNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
