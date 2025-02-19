#ifndef DO_WHILE_NODE_H
#define DO_WHILE_NODE_H

#include "loop_node.h"

namespace ParseNodes::Loops
{
    class DoWhileNode final : public LoopNode
    {
        public:
            DoWhileNode(const ParseNode* condition, const Groups::ScopeNode* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
