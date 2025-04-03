#ifndef DECLARATION_NODE_H
#define DECLARATION_NODE_H

#include "../Core/characteristic_node.h"

namespace ParseNodes::Statements
{
    class DeclarationNode : public virtual FixedNodeCollection<3>, public Core::CharacteristicNode<3>
    {
        public:
            DeclarationNode(const Describers::DescriberNode* describer, const ParseNode* type, const Values::IdentifierNode* identifier, const Tokens::Token& separator);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
