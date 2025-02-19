#ifndef LOOP_NODE_H
#define LOOP_NODE_H

#include "../../../Lexing//Tokens/token.h"

#include "../parse_node.h"
#include "../Core/body_node.h"

namespace ParseNodes::Loops
{
    class LoopNode : public ParseNode, public Core::BodyNode
    {
        protected:
            const ParseNode* condition;

            const Tokens::Token& keyword;

        public:
            LoopNode(const ParseNode* condition, const Groups::ScopeNode* body, const Tokens::Token& keyword);

            [[nodiscard]] const ParseNode* Condition() const;

            [[nodiscard]] unsigned long Index() const override;

            ~LoopNode() override;
    };
}

#endif
