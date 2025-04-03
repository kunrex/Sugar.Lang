#ifndef CONSTRUCTOR_CREATION_NODE_H
#define CONSTRUCTOR_CREATION_NODE_H

#include "../../parse_node.h"
#include "../../Core/body_node.h"
#include "../../Core/describable_node.h"
#include "../../Groups/compound_declaration_node.h"

namespace ParseNodes::Functions::Creation
{
    class ConstructorCreationNode final : public virtual FixedNodeCollection<3>, public Core::DescribableNode<3>, public Core::BodyNode<3>
    {
        public:
            ConstructorCreationNode(const Describers::DescriberNode* describer, const Groups::CompoundDeclarationNode* parameters, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
