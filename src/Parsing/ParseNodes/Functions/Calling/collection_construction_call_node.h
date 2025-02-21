#ifndef COLLECTION_CONSTRUCTION_CALL_NODE_H
#define COLLECTION_CONSTRUCTION_CALL_NODE_H

#include "../../Groups/scope_node.h"

namespace ParseNodes::Functions::Calling
{
    class CollectionConstructorCallNode final : public ParseNode
    {
        private:
            const ParseNode* type;
            const Groups::ScopeNode* scope;

        public:
            explicit CollectionConstructorCallNode(const ParseNode* type, const Groups::ScopeNode* scope);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] unsigned long Index() const override;

            ~CollectionConstructorCallNode() override;
    };
}

#endif
