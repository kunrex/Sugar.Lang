#ifndef UNARY_NODE_H
#define UNARY_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Expressions
{
    class UnaryNode final : public FixedNodeCollection<1>
    {
        public:
            UnaryNode(const Tokens::Token& base, const ParseNode* operand);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
