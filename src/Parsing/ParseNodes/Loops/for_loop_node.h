#ifndef FOR_NODE_H
#define FOR_NODE_H

#include "loop_node.h"
#include "../Statements/statement_node.h"

namespace ParseNodes::Loops
{
    class ForLoopNode final : public LoopNode
    {
        private:
            const ParseNode* pre;
            const ParseNode* post;

        public:
            ForLoopNode(const ParseNode* pre, const ParseNode* condition, const ParseNode* post, const NodeCollection<ParseNode>* body, const Tokens::Token& keyword);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const ParseNode* Pre() const;
            [[nodiscard]] const ParseNode* Post() const;

            ~ForLoopNode() override;
    };
}

#endif
