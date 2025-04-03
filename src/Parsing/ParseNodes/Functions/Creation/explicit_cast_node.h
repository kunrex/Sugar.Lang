#ifndef EXPLICIT_CAST_NODE_H
#define EXPLICIT_CAST_NODE_H

#include "../../Core/function_node.h"

namespace ParseNodes::Functions::Creation
{
    class ExplicitCastNode final : public virtual FixedNodeCollection<4>, public Core::FunctionNode<4>
    {
        public:
            ExplicitCastNode(const Describers::DescriberNode* describer, const ParseNode* type, const Groups::CompoundDeclarationNode* parameters, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
