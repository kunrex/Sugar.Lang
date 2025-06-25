#include "constructor_definition.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Creation
{
    ConstructorDefinition::ConstructorDefinition(const Enums::Describer describer, const IDataType* const creationType) : Function(describer, creationType)
    { }
}
