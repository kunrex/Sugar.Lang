#ifndef NULL_NODE_H
#define NULL_NODE_H

#include "value_node.h"

namespace ParseNodes::Values
{
    class NullNode final : public ValueNode
    {
        public:
            explicit NullNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
