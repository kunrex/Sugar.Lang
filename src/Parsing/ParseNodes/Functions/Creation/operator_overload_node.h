#ifndef OPERATOR_OVERLOAD_NODE_H
#define OPERATOR_OVERLOAD_NODE_H

#include "../../Core/function_node.h"

namespace ParseNodes::Functions::Creation
{
    class OperatorOverloadNode final : public virtual FixedNodeCollection<4>, public Core::FunctionNode<4>
    {
        public:
            OperatorOverloadNode(const Describers::DescriberNode* describer, const ParseNode* type, const Tokens::Token& base, const Groups::CompoundDeclarationNode* parameters, const DynamicNodeCollection* body);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
