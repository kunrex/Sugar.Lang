#ifndef BASE_INDEXER_NODE_H
#define BASE_INDEXER_NODE_H

#include "Accessors/get_node.h"
#include "Accessors/set_node.h"

#include "../parse_node.h"
#include "../Groups/compound_declaration_node.h"

namespace ParseNodes::Properties
{
    class BaseIndexerNode final : public virtual FixedNodeCollection<5>
    {
        public:
            BaseIndexerNode(const Describers::DescriberNode* describer, const IParseNode* type, const Groups::MultipleDeclarationNode* parameters, const IParseNode* get, const IParseNode* set, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
