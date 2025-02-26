#include "cast_definition.h"

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Creation
{
    CastDefinition::CastDefinition(const Enums::Describer describer, const IDataType* const creationType) : Function(describer, creationType)
    { }
}
