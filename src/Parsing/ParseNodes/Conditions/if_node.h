#ifndef IF_NODE_H
#define IF_NODE_H

#include "condition_node.h"

namespace ParseNodes::Conditions
{
    class IfNode final : public ConditionNode
    {
        public:
            IfNode(const ParseNode* condition, const ParseNode* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
