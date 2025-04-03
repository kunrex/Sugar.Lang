#ifndef BASE_INDEXER_NODE_H
#define BASE_INDEXER_NODE_H

#include "Accessors/get_node.h"
#include "Accessors/set_node.h"

#include "../Core/entity_node.h"
#include "../Groups/compound_declaration_node.h"

namespace ParseNodes::Properties
{
    class BaseIndexerNode final : public virtual FixedNodeCollection<>
    {
        public:
            BaseIndexerNode(const Describers::DescriberNode* describer, const ParseNode* type, const Groups::CompoundDeclarationNode* parameters, const GetNode* get, const SetNode* set, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
