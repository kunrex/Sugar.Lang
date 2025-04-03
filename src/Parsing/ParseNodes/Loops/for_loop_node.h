#ifndef FOR_NODE_H
#define FOR_NODE_H

#include "../parse_node.h"
#include "../Core/body_node.h"

namespace ParseNodes::Loops
{
    class ForLoopNode final : public virtual FixedNodeCollection<4>, public Core::BodyNode<4>
    {
        public:
            ForLoopNode(const ParseNode* pre, const ParseNode* condition, const ParseNode* post, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
