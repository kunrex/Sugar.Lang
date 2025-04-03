#ifndef WHILE_NODE_H
#define WHILE_NODE_H

#include "loop_node.h"

namespace ParseNodes::Loops
{
    class WhileNode final : public LoopNode
    {
        public:
            WhileNode(const ParseNode* condition, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
