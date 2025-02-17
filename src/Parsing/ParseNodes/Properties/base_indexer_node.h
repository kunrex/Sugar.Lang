#ifndef BASE_INDEXER_NODE_H
#define BASE_INDEXER_NODE_H

#include "../parse_node.h"
#include "../Core/entity_node.h"
#include "../Core/property_node.h"
#include "../../../Lexing/Tokens/token.h"
#include "../Groups/compound_declaration_node.h"

namespace ParseNodes::Properties
{
    class BaseIndexerNode final : public ParseNode, public Core::DescribableNode, public Core::EntityNode, public Core::PropertyNode
    {
        private:
            const Groups::CompoundDeclarationNode* parameters;

            const Tokens::Token& keyword;

        public:
            BaseIndexerNode(const Describers::DescriberNode* describer, const ParseNode* type, const Groups::CompoundDeclarationNode* parameters, const GetNode* get, const SetNode* set, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const Groups::CompoundDeclarationNode* Parameters() const;

            [[nodiscard]] unsigned long Index() const override;

            ~BaseIndexerNode() override;
    };
}

#endif
