#ifndef LOOP_NODE_H
#define LOOP_NODE_H

#include "../../../Lexing//Tokens/token.h"

#include "../parse_node.h"
#include "../Core/body_node.h"

namespace ParseNodes::Loops
{
    class LoopNode : public virtual FixedNodeCollection<2>, public Core::BodyNode<2>
    {
        public:
            LoopNode(const ParseNode* condition, const DynamicNodeCollection* body, const Tokens::Token& keyword);
    };
}

#endif
