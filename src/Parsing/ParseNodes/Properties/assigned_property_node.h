#ifndef ASSIGNED_PROPERTY_NODE_H
#define ASSIGNED_PROPERTY_NODE_H

#include "base_property_node.h"

namespace ParseNodes::Properties
{
    class AssignedPropertyNode final : public BasePropertyNode
    {
        public:
            AssignedPropertyNode(const Describers::DescriberNode* describer, const ParseNode* type, const Values::IdentifierNode* identifier, const GetNode* get, const SetNode* set, const ParseNode* value);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}


#endif
