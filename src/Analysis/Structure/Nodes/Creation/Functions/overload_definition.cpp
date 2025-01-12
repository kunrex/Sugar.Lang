#include "overload_definition.h"

using namespace Tokens;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    OverloadDefinition::OverloadDefinition(const Token& baseOperator, const Enums::Describer describer, const DataType* creationType) : Function(describer, creationType), baseOperator(baseOperator)
    { }
}
