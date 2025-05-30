#ifndef CONSTRUCTOR_CREATION_NODE_H
#define CONSTRUCTOR_CREATION_NODE_H

#include "../../parse_node.h"
#include "../../Describers/describer_node.h"
#include "../../Groups/compound_declaration_node.h"

namespace ParseNodes::Functions::Creation
{
    class ConstructorCreationNode final : public virtual FixedNodeCollection<3>
    {
        public:
            ConstructorCreationNode(const Describers::DescriberNode* describer, const Groups::MultipleDeclarationNode* parameters, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
