#include "built_in_indexer.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInIndexer::BuiltInIndexer(const DataType* creationType, std::string getInstruction, std::string setInstruction) : IndexerDefinition(Describer::Public, creationType), getInstruction(std::move(getInstruction)), setInstruction(std::move(setInstruction))
    { }

    std::string BuiltInIndexer::GetInstruction() const { return getInstruction; }
    std::string BuiltInIndexer::SetInstruction() const { return setInstruction; }
}

