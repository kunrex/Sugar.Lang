#ifndef FUNCTION_NODE_H
#define FUNCTION_NODE_H

#include "body_node.h"
#include "entity_node.h"
#include "describable_node.h"

#include "../Groups/compound_declaration_node.h"

namespace ParseNodes::Core
{
    class FunctionNode : public DescribableNode, public EntityNode, public BodyNode
    {
        protected:
            const Groups::CompoundDeclarationNode* parameters;

            FunctionNode(const Describers::DescriberNode* describer, const ParseNode* type, const Groups::CompoundDeclarationNode* parameters, const NodeCollection<ParseNode>* body);

        public:
            [[nodiscard]] const Groups::CompoundDeclarationNode* Parameters() const;

            ~FunctionNode() override;
    };
}

#endif
