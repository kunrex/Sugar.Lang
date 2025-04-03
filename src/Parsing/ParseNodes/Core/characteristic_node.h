#ifndef CHARACTERISTIC_NODE_H
#define CHARACTERISTIC_NODE_H

#include "entity_node.h"
#include "nameable_node.h"
#include "describable_node.h"

namespace ParseNodes::Core
{
    template <int childCount>
    class CharacteristicNode : public DescribableNode<childCount>, public EntityNode<childCount>, public NameableNode<childCount>
    {
        protected:
            CharacteristicNode(const Describers::DescriberNode* describer, const ParseNode* type, const Values::IdentifierNode* identifier);
    };
}

#endif
