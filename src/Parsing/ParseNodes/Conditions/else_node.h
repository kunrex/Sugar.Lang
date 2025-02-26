#ifndef ELSE_NODE_H
#define ELSE_NODE_H

#include "condition_node.h"

namespace ParseNodes::Conditions
{
    class ElseNode final : public ConditionNode
    {
        public:
            ElseNode(const NodeCollection<ParseNode>* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
