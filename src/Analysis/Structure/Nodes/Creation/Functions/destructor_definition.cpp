#include "destructor_definition.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    DestructorDefinition::DestructorDefinition(const Enums::Describer describer, const DataType* creationType) : Function(describer, creationType)
    { }
}

