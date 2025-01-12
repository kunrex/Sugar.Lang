#include "built_in_operation.h"

using namespace std;

using namespace Tokens::Operators;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Global
{
    BuiltInOperation::BuiltInOperation(const Tokens::Operators::Operator* baseOperator, const DataType* creationType, const string& instruction) : OverloadDefinition(baseOperator, Describer::PublicStatic, creationType), BuiltInInstruction(instruction)
    { }
}
