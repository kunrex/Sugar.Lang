#ifndef DOT_EXPRESSION_NODE_H
#define DOT_EXPRESSION_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Expressions
{
    class DotExpressionNode : public FixedNodeCollection<2>
    {
        public:
            DotExpressionNode(const IParseNode* lhs, const IParseNode* rhs, const Tokens::Token& dot);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
