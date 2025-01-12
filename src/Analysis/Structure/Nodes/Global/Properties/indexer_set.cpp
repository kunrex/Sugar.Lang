#include "indexer_set.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Global
{
    IndexerSet::IndexerSet(const Enums::Describer describer, const DataType* creationType, Creation::Set* get) : IndexerDefinition(describer, creationType), Setable(get)
    { }
}

