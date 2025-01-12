#ifndef INITIALISATION_NODE_H
#define INITIALISATION_NODE_H

#include "../parse_node.h"
#include "declaration_node.h"

namespace ParseNodes::Statements
{
    class InitialisationNode final : public DeclarationNode
    {
        private:
            const ParseNode* value;

        public:
            InitialisationNode(const Describers::DescriberNode* describer, const ParseNode* type, const Values::IdentifierNode* identifier, const ParseNode* value, const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const ParseNode* Value() const;

            ~InitialisationNode() override;
    };
}

#endif
