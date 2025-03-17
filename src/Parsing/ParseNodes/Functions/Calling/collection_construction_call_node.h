#ifndef COLLECTION_CONSTRUCTION_CALL_NODE_H
#define COLLECTION_CONSTRUCTION_CALL_NODE_H

#include "../../parse_node.h"

namespace ParseNodes::Functions::Calling
{
    class CollectionConstructorCallNode final : public NodeCollection<ParseNode>
    {
        private:
            const ParseNode* type;

        public:
            explicit CollectionConstructorCallNode(const ParseNode* type);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] unsigned long Index() const override;

            [[nodiscard]] const ParseNode* Type() const;

            ~CollectionConstructorCallNode() override;
    };
}

#endif
