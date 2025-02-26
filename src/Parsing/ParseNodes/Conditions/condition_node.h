#ifndef CONDITION_NODE_H
#define CONDITION_NODE_H

#include "../Core/body_node.h"
#include "../../../Lexing/Tokens/token.h"

namespace ParseNodes::Conditions
{
    class ConditionNode : public ParseNode, public Core::BodyNode
    {
        protected:
            const ParseNode* condition;

            const Tokens::Token& keyword;

            ConditionNode(const ParseNode* condition, const NodeCollection<ParseNode>* body, const Tokens::Token& keyword);

        public:
            [[nodiscard]] virtual const ParseNode* Condition() const;

            [[nodiscard]] unsigned long Index() const override;

            ~ConditionNode() override;
    };
}

#endif //CONDITION_NODE_H
