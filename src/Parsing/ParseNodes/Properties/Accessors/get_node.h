#ifndef GET_NODE_H
#define GET_NODE_H

#include "accessor_node.h"

namespace ParseNodes::Properties
{
    class GetNode final : public AccessorNode
    {
        public:
            GetNode(const Describers::DescriberNode* describer, const DynamicNodeCollection* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;
    };
}

#endif
