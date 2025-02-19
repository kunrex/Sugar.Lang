#include "indexer_definition.h"

using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Creation
{
    IndexerDefinition::IndexerDefinition(const Enums::Describer describer, const DataType* const creationType) : GlobalNode(), Describable(describer), Created(creationType)
    { }
}
