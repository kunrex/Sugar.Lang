#ifndef IF_CHAIN_NODE_H
#define IF_CHAIN_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Groups
{
    class IfChainNode final : public DynamicNodeCollection
    {
        public:
            explicit IfChainNode(const Tokens::Token& token);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
