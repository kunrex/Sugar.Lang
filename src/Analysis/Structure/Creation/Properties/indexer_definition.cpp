#include "indexer_definition.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Creation
{
    IndexerDefinition::IndexerDefinition(const Enums::Describer describer, const IDataType* const creationType) : Describable(describer), Created(creationType)
    { }
}
