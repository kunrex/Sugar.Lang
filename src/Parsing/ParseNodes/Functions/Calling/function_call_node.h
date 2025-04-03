#ifndef FUNCTION_CALL_NODE_H
#define FUNCTION_CALL_NODE_H

#include "../../Values/identifier_node.h"

namespace ParseNodes::Functions::Calling
{
    class FunctionCallNode final : public DynamicNodeCollection
    {
        public:
            explicit FunctionCallNode(const Values::IdentifierNode* identifier);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
