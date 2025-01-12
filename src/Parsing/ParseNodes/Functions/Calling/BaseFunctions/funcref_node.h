#ifndef FUNCREF_NODE_H
#define FUNCREF_NODE_H

#include "base_function_call_node.h"
#include "../../../Groups/generic_node.h"

namespace ParseNodes::Functions::Calling
{
    class FuncRefNode final : public BaseFunctionCallNode
    {
        private:
            const Groups::GenericNode* generic;

        public:
            FuncRefNode(const Groups::GenericNode* generic, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const Groups::GenericNode* Generic() const;

            ~FuncRefNode() override;
    };
}

#endif
