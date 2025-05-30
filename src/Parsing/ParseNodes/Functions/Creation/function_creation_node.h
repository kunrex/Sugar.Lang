#ifndef FUNCTION_CREATION_NODE_H
#define FUNCTION_CREATION_NODE_H

#include "../../parse_node.h"
#include "../../Values/identifier_node.h"
#include "../../Describers/describer_node.h"
#include "../../Groups/compound_declaration_node.h"

namespace ParseNodes::Functions::Creation
{
    class FunctionCreationNode final : public virtual FixedNodeCollection<5>
    {
        public:
            FunctionCreationNode(const Describers::DescriberNode* describer, const IParseNode* type, const Values::IdentifierNode* identifier, const Groups::MultipleDeclarationNode* parameters, const DynamicNodeCollection* body);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
