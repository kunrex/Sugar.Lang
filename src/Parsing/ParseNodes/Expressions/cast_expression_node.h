#ifndef CAST_EXPRESSION_NODE_H
#define CAST_EXPRESSION_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Expressions
{
    class CastExpressionNode final : public FixedNodeCollection<2>
    {
        public:
            CastExpressionNode(const IParseNode* lhs, const IParseNode* rhs, const Tokens::Token& as);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
