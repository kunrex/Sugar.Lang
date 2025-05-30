#ifndef IMPLICIT_CAST_NODE_H
#define IMPLICIT_CAST_NODE_H

#include "../../parse_node.h"
#include "../../Describers/describer_node.h"
#include "../../Groups/compound_declaration_node.h"

namespace ParseNodes::Functions::Creation
{
    class ImplicitCastNode final : public virtual FixedNodeCollection<4>
    {
        public:
            ImplicitCastNode(const Describers::DescriberNode* describer, const IParseNode* type, const Groups::MultipleDeclarationNode* parameters, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
