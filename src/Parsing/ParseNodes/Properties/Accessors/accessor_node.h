#ifndef ACCESSOR_NODE_H
#define ACCESSOR_NODE_H

#include "../../../../Lexing/Tokens/token.h"

#include "../../parse_node.h"
#include "../../Core/body_node.h"
#include "../../Core/describable_node.h"

namespace ParseNodes::Properties
{
    class AccessorNode : public virtual FixedNodeCollection<2>, public Core::DescribableNode<2>, public Core::BodyNode<2>
    {
        public:
            AccessorNode(const Describers::DescriberNode* describer, const DynamicNodeCollection* body, const Tokens::Token& keyword);
    };
}

#endif
