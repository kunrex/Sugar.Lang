#include "built_in_index_instruction.h"

using namespace Analysis::Structure::Global;

namespace Analysis::Structure::Context
{
    BuiltInIndexerInstruction::BuiltInIndexerInstruction(const BuiltInIndexer* indexer, const ContextNode* operand) : UnaryContextNode(indexer->CreationType(), operand), indexer(indexer)
    { }

    std::string BuiltInIndexerInstruction::InstructionGet() const { return indexer->GetInstruction(); }
    std::string BuiltInIndexerInstruction::InstructionSet() const { return indexer->SetInstruction(); }
}
