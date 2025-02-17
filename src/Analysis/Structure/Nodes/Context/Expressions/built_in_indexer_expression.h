#ifndef BUILT_IN_INDEXER_EXPRESSION_H
#define BUILT_IN_INDEXER_EXPRESSION_H

#include "../unary_context_node.h"
#include "../../Creation/Properties/indexer_definition.h"

namespace Analysis::Structure::Context
{
    class BuiltInIndexerExpression final : public UnaryContextNode, public Services::ConstantCollection<ContextNode>
    {
        private:
            const bool readable;
            const bool writable;

            const std::string getInstruction;
            const std::string setInstruction;

        public:
            explicit BuiltInIndexerExpression(const Creation::IndexerDefinition* indexer, const ContextNode* operand);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;

            [[nodiscard]] int SlotCount() const override;
    };
}

#endif
