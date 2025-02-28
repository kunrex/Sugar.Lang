#ifndef BUILT_IN_INDEXER_EXPRESSION_H
#define BUILT_IN_INDEXER_EXPRESSION_H

#include "../unary_context_node.h"

namespace Analysis::Structure::Context
{
    class BuiltInIndexerExpression final : public UnaryContextNode, public Services::ConstantCollection<ContextNode>
    {
        private:
            mutable int slotCount;
            const bool isLoadInstruction;
            const Core::Interfaces::IIndexerDefinition* indexer;

        public:
            BuiltInIndexerExpression(const Core::Interfaces::IIndexerDefinition* indexer, const ContextNode* operand, bool isLoadInstruction);

            [[nodiscard]] Enums::MemberType MemberType() const override;

            [[nodiscard]] int SlotCount() const override;

            [[nodiscard]] bool Readable() const override;
            [[nodiscard]] bool Writable() const override;

            [[nodiscard]] std::string CILInstruction() const override;
    };
}

#endif
