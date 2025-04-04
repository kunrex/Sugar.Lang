#ifndef INDEXER_EXPRESSION_H
#define INDEXER_EXPRESSION_H

#include "../context_node.h"

#include "../../Core/Interfaces/Creation/i_indexer_definition.h"

namespace Analysis::Structure::Context
{
    class IndexerExpression final : public DynamicContextCollection
    {
        private:
            mutable int slotCount;
            const Core::Interfaces::IIndexerDefinition* indexer;

        public:
            IndexerExpression(const Core::Interfaces::IIndexerDefinition* indexer, const IContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILData() const override;
            [[nodiscard]] uintptr_t Metadata() const override;
    };
}

#endif
