#ifndef DECLARATION_NODE_H
#define DECLARATION_NODE_H

#include "statement_node.h"
#include "../Core/characteristic_node.h"

namespace ParseNodes::Statements
{
    class DeclarationNode : public StatementNode, public Core::CharacteristicNode
    {
        public:
            DeclarationNode(const Describers::DescriberNode* describer, const ParseNode* type, const Values::IdentifierNode* identifier, const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] unsigned long Index() const override;
    };
}

#endif
