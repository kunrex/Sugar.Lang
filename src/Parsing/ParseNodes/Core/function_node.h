#ifndef FUNCTION_NODE_H
#define FUNCTION_NODE_H

#include "body_node.h"
#include "entity_node.h"
#include "describable_node.h"

#include "../Groups/compound_declaration_node.h"

namespace ParseNodes::Core
{
    template <int childCount>
    class FunctionNode : public DescribableNode<childCount>, public EntityNode<childCount>, public BodyNode<childCount>
    {
        protected:
            FunctionNode(const Describers::DescriberNode* describer, const ParseNode* type, const Groups::CompoundDeclarationNode* parameters, const DynamicNodeCollection* body);
    };
}

#endif
