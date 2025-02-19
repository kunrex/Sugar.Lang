#include "constructor_definition.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    ConstructorDefinition::ConstructorDefinition(const Enums::Describer describer, const DataType* const creationType) : Function(describer, creationType)
    { }
}
