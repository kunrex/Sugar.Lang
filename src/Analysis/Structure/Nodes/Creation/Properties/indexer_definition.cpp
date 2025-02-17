#include "indexer_definition.h"

using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Creation
{
    IndexerDefinition::IndexerDefinition(Enums::Describer describer, const DataType* creationType) : GlobalNode(), Describable(describer), Created(creationType)
    { }
}
