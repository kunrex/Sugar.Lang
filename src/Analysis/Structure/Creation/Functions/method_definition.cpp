#include "method_definition.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    MethodDefinition::MethodDefinition(const string& name, const Enums::Describer describer, const DataType* const creationType) : FunctionDefinition(name, describer, creationType)
    { }
}
