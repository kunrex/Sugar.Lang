#ifndef INDEXER_EXPRESSION_H
#define INDEXER_EXPRESSION_H

#include "../context_node.h"
#include "../unary_context_node.h"

#include "../../Creation/Properties/indexer_definition.h"

#include "../../../../Services/collection.h"

namespace Analysis::Structure::Context
{
    class IndexerExpression final : public UnaryContextNode, public Services::ConstantCollection<ContextNode>
    {
        private:
            mutable int slotCount;
            const Core::Interfaces::IIndexerDefinition* indexer;

        public:
            IndexerExpression(const Core::Interfaces::IIndexerDefinition* indexer, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;

            [[nodiscard]] const Core::Interfaces::IIndexerDefinition* Indexer() const;
    };
}

#endif
