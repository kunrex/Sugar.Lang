#ifndef OVERLOADED_INDEXER_EXPRESSION_H
#define OVERLOADED_INDEXER_EXPRESSION_H

#include "../context_node.h"
#include "../unary_context_node.h"
#include "../../Creation/Properties/indexer_definition.h"

namespace Analysis::Structure::Context
{
    class OverloadedIndexerExpression final : public UnaryContextNode, public Services::Collection<ContextNode>
    {
        private:
            const Creation::IndexerDefinition* indexer;

        public:
            explicit OverloadedIndexerExpression(const Creation::IndexerDefinition* indexer, const ContextNode* operand);

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
