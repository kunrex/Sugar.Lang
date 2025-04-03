#ifndef TERNARY_NODE_H
#define TERNARY_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Expressions
{
    class TernaryNode final : public FixedNodeCollection<3>
    {
        public:
            TernaryNode(const ParseNode* condition, const ParseNode* trueValue, const ParseNode* falseValue, const Tokens::Token& questionMark);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
