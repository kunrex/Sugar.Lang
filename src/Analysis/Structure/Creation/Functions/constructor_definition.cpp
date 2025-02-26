#include "constructor_definition.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Creation
{
    ConstructorDefinition::ConstructorDefinition(const Enums::Describer describer, const IDataType* const creationType) : Function(describer, creationType)
    { }
}
