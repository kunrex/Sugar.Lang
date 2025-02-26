#ifndef SET_NODE_H
#define SET_NODE_H

#include "accessor_node.h"

namespace ParseNodes::Properties
{
    class SetNode final : public AccessorNode
    {
        public:
            SetNode(const Describers::DescriberNode* describer, const NodeCollection<ParseNode>* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
