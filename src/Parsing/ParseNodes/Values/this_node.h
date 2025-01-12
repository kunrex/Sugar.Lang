#ifndef THIS_NODE_H
#define THIS_NODE_H

#include "value_node.h"

namespace ParseNodes::Values
{
    class ThisNode final : public ValueNode
    {
        public:
            explicit ThisNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
