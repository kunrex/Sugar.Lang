#ifndef IF_NODE_H
#define IF_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Conditions
{
    class IfNode final : public FixedNodeCollection<2>
    {
        public:
            IfNode(const ParseNode* condition, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
