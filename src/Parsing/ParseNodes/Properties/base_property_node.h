#ifndef BASE_PROPERTY_NODE_H
#define BASE_PROPERTY_NODE_H

#include "../parse_node.h"
#include "../Core/property_node.h"
#include "../Values/identifier_node.h"
#include "../Core/characteristic_node.h"

namespace ParseNodes::Properties
{
    class BasePropertyNode final : public ParseNode, public Core::CharacteristicNode, public Core::PropertyNode
    {
        public:
            BasePropertyNode(const Describers::DescriberNode* describer, const ParseNode* type, const Values::IdentifierNode* identifier, const GetNode* get, const SetNode* set);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
