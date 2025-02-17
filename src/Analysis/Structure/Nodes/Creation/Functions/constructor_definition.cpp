#include "constructor_definition.h"

#include <format>

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    ConstructorDefinition::ConstructorDefinition(const Enums::Describer describer, const DataType* creationType) : Function(describer, creationType)
    { }
}
