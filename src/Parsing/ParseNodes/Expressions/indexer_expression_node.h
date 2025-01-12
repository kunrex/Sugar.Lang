#ifndef INDEXER_EXPRESSION_NODE_H
#define INDEXER_EXPRESSION_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Expressions
{
    class IndexerExpressionNode final : public NodeCollection<ParseNode>
    {
        private:
            const ParseNode* operand;

        public:
            explicit IndexerExpressionNode(const ParseNode* operand);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            [[nodiscard]] const ParseNode* Operand() const;

            ~IndexerExpressionNode() override;
    };
}

#endif
