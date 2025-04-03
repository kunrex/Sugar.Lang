#ifndef BASE_PROPERTY_NODE_H
#define BASE_PROPERTY_NODE_H

#include "../parse_node.h"
#include "../Core/entity_node.h"
#include "../Core/nameable_node.h"
#include "../Core/property_node.h"
#include "../Core/describable_node.h"
#include "../Values/identifier_node.h"

namespace ParseNodes::Properties
{
    class BasePropertyNode : public virtual FixedNodeCollection<5>, public Core::DescribableNode<5>, public Core::EntityNode<5>, public Core::NameableNode<5>, public Core::PropertyNode<5>
    {
        public:
            BasePropertyNode(const Describers::DescriberNode* describer, const ParseNode* type, const Values::IdentifierNode* identifier, const GetNode* get, const SetNode* set);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
