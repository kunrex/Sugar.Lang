#ifndef ARRAY_INDEX_INSTRUCTION_H
#define ARRAY_INDEX_INSTRUCTION_H

#include "../context_node.h"
#include "../unary_context_node.h"
#include "../../Global/BuiltIn/built_in_indexer.h"

namespace Analysis::Structure::Context
{
    class BuiltInIndexerInstruction final : public UnaryContextNode
    {
        private:
            const Global::BuiltInIndexer* indexer;

        public:
            explicit BuiltInIndexerInstruction(const Global::BuiltInIndexer* indexer, const ContextNode* operand);

            [[nodiscard]] std::string InstructionGet() const override;
            [[nodiscard]] std::string InstructionSet() const override;
    };
}

#endif
