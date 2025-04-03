#ifndef NULL_NODE_H
#define NULL_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Values
{
    class NullNode final : public ParseNode
    {
        public:
            explicit NullNode(const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
