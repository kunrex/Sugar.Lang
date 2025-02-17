#ifndef CHARACTERISTIC_NODE_H
#define CHARACTERISTIC_NODE_H

#include "entity_node.h"
#include "nameable_node.h"
#include "describable_node.h"

namespace ParseNodes::Core
{
    class CharacteristicNode : public DescribableNode, public EntityNode, public NameableNode
    {
        protected:
            CharacteristicNode(const Describers::DescriberNode* describer, const ParseNode* type, const Values::IdentifierNode* identifier);
    };
}

#endif
