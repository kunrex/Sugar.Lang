#include "function_definition.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    FunctionDefinition::FunctionDefinition(const string& name, const Enums::Describer describer, const DataType* creationType) : Nameable(name), Function(describer, creationType)
    { }
}

