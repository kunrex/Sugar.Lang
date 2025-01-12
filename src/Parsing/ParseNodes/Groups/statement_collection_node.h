#ifndef EXPRESSION_LIST_NODE_H
#define EXPRESSION_LIST_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Groups
{
    class ExpressionListNode final : public NodeCollection<ParseNode>
    {
        public:
            ExpressionListNode();

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
