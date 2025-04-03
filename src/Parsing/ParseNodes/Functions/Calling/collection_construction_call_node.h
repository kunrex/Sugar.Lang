#ifndef COLLECTION_CONSTRUCTION_CALL_NODE_H
#define COLLECTION_CONSTRUCTION_CALL_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class CollectionConstructorCallNode final : public DynamicNodeCollection
    {
        public:
            CollectionConstructorCallNode(const ParseNode* type, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
