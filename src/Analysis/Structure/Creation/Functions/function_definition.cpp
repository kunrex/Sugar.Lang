#include "function_definition.h"

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Creation
{
    FunctionDefinition::FunctionDefinition(const string& name, const Enums::Describer describer, const IDataType* const creationType) : Nameable(name), Function(describer, creationType)
    { }
}