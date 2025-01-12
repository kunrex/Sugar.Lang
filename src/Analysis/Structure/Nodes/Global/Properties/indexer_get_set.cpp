#include "indexer_get_set.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Global
{
    IndexerGetSet::IndexerGetSet(const Enums::Describer describer, const DataType* creationType, Creation::Get* get, Creation::Set* set) : IndexerDefinition(describer, creationType), GetSet(get, set)
    { }
}

