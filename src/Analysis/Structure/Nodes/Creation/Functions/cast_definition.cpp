#include "cast_definition.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    CastDefinition::CastDefinition(const Enums::Describer describer, const DataType* creationType) : Function(describer, creationType)
    { }
}
