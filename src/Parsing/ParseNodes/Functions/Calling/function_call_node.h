#ifndef FUNCTION_CALL_NODE_H
#define FUNCTION_CALL_NODE_H

#include "../../Values/identifier_node.h"

namespace ParseNodes::Functions::Calling
{
    class FunctionCallNode final : public NodeCollection<ParseNode>
    {
        private:
            const Values::IdentifierNode* identifier;

        public:
            explicit FunctionCallNode(const Values::IdentifierNode* identifier);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const Values::IdentifierNode* Identifier() const;

            ~FunctionCallNode() override;
    };
}

#endif
