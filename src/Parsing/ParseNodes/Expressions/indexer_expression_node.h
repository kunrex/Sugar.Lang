#ifndef INDEXER_EXPRESSION_NODE_H
#define INDEXER_EXPRESSION_NODE_H

#include "../parse_node.h"

namespace ParseNodes::Expressions
{
    class IndexerExpressionNode final : public DynamicNodeCollection
    {
        public:
            explicit IndexerExpressionNode(const IParseNode* operand);

            [[nodiscard]] Enums::NodeType NodeType() const override;

            void Print(const std::string& indent, bool last) const override;
    };
}

#endif
