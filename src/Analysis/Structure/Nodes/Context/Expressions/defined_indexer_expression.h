#ifndef DEFINED_INDEXER_EXPRESSION_H
#define DEFINED_INDEXER_EXPRESSION_H

#include "../context_node.h"
#include "../unary_context_node.h"
#include "../../../../../Services/collection.h"
#include "../../Creation/Properties/indexer_definition.h"

namespace Analysis::Structure::Context
{
    class DefinedIndexerExpression final : public UnaryContextNode, public Services::ConstantCollection<ContextNode>
    {
        private:
            mutable bool readable;
            mutable bool writable;

            mutable std::string getInstruction;
            mutable std::string setInstruction;

        public:
            explicit DefinedIndexerExpression(const Creation::IndexerDefinition* indexer, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;

            [[nodiscard]] int SlotCount() const override;
    };
}

#endif
