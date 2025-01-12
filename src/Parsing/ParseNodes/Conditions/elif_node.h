#ifndef ELIF_NODE_H
#define ELIF_NODE_H

#include "condition_node.h"

namespace ParseNodes::Conditions
{
    class ElifNode final : public ConditionNode
    {
        public:
            ElifNode(const ParseNode* condition, const ParseNode* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
