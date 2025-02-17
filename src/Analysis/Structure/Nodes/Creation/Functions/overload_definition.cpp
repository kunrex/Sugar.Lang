#include "overload_definition.h"

#include "../../../Core/DataTypes/data_type.h"

using namespace Tokens::Enums;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    OverloadDefinition::OverloadDefinition(const SyntaxKind baseOperator, const Enums::Describer describer, const DataType* creationType) : Function(describer, creationType), baseOperator(baseOperator)
    { }

    SyntaxKind OverloadDefinition::Operator() const { return baseOperator; }
}
