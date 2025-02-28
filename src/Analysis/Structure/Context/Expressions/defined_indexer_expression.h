#ifndef DEFINED_INDEXER_EXPRESSION_H
#define DEFINED_INDEXER_EXPRESSION_H

#include "../context_node.h"
#include "../unary_context_node.h"

#include "../../Creation/Properties/indexer_definition.h"

#include "../../../../Services/collection.h"

namespace Analysis::Structure::Context
{
    class DefinedIndexerExpression final : public UnaryContextNode, public Services::ConstantCollection<ContextNode>
    {
        private:
            mutable int slotCount;
            const bool isLoadInstruction;
            const Core::Interfaces::IIndexerDefinition* indexer;

        public:
            DefinedIndexerExpression(const Core::Interfaces::IIndexerDefinition* indexer, const ContextNode* operand, bool isLoadInstruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILInstruction() const override;
    };
}

#endif
