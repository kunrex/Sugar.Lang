#ifndef IMPLICIT_CAST_NODE_H
#define IMPLICIT_CAST_NODE_H

#include "../../Core/function_node.h"

namespace ParseNodes::Functions::Creation
{
    class ImplicitCastNode final : public virtual FixedNodeCollection<4>, public Core::FunctionNode<4>
    {
        public:
            ImplicitCastNode(const Describers::DescriberNode* describer, const ParseNode* type, const Groups::CompoundDeclarationNode* parameters, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
