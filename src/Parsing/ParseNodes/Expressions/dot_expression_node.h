#ifndef DOT_EXPRESSION_NODE_H
#define DOT_EXPRESSION_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Expressions
{
    class DotExpressionNode : public FixedNodeCollection<2>
    {
        public:
            DotExpressionNode(const ParseNode* lhs, const ParseNode* rhs, const Tokens::Token& dot);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
