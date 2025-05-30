#ifndef OPERATOR_OVERLOAD_NODE_H
#define OPERATOR_OVERLOAD_NODE_H

#include "../../parse_node.h"
#include "../../Describers/describer_node.h"
#include "../../Groups/compound_declaration_node.h"

namespace ParseNodes::Functions::Creation
{
    class OperatorOverloadNode final : public virtual FixedNodeCollection<4>
    {
        public:
            OperatorOverloadNode(const Describers::DescriberNode* describer, const IParseNode* type, const Tokens::Token& base, const Groups::MultipleDeclarationNode* parameters, const DynamicNodeCollection* body);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
