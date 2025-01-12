#ifndef IF_CHAIN_NODE_H
#define IF_CHAIN_NODE_H

#include "../parse_node.h"
#include "../Conditions/condition_node.h"

namespace ParseNodes::Groups
{
    class IfChainNode final : public NodeCollection<Conditions::ConditionNode>
    {
        public:
            IfChainNode();

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
