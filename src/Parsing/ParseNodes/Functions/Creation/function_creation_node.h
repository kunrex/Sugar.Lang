#ifndef FUNCTION_CREATION_NODE_H
#define FUNCTION_CREATION_NODE_H

#include "../../Core/function_node.h"

namespace ParseNodes::Functions::Creation
{
    class FunctionCreationNode final : public virtual FixedNodeCollection<5>, public Core::FunctionNode<5>, public Core::NameableNode<5>
    {
        public:
            FunctionCreationNode(const Describers::DescriberNode* describer, const ParseNode* type, const Values::IdentifierNode* identifier, const Groups::CompoundDeclarationNode* parameters, const DynamicNodeCollection* body);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
