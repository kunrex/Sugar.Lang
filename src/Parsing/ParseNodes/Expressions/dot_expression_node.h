#ifndef DOT_EXPRESSION_NODE_H
#define DOT_EXPRESSION_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Expressions
{
    class DotExpressionNode : public ParseNode
    {
        private:
            const ParseNode* lhs;
            const ParseNode* rhs;

        public:
            DotExpressionNode(const ParseNode* lhs, const ParseNode* rhs);

            [[nodiscard]] const ParseNode* LHS() const;
            [[nodiscard]] const ParseNode* RHS() const;

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] unsigned long Index() const override;

            ~DotExpressionNode() override;
    };
}

#endif //DOT_EXPRESSION_NODE_H
