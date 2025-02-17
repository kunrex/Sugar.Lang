#ifndef EXPRESSION_LIST_NODE_H
#define EXPRESSION_LIST_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Groups
{
    class ExpressionListNode final : public NodeCollection<ParseNode>
    {
        private:
            const unsigned long index;

        public:
            explicit ExpressionListNode(unsigned long index);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
