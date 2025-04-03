#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Expressions
{
    class BinaryNode final : public FixedNodeCollection<2>
    {
        public:
            BinaryNode(const Tokens::Token& base, const ParseNode* lhs, const ParseNode* rhs);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
