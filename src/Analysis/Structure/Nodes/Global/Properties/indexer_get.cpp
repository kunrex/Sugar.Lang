#include "indexer_get.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Global
{
    IndexerGet::IndexerGet(const Enums::Describer describer, const DataType* creationType, Creation::Get* get) : IndexerDefinition(describer, creationType), Getable(get)
    { }
}
