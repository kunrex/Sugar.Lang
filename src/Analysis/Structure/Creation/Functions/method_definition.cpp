#include "method_definition.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Core;
using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Creation
{
    MethodDefinition::MethodDefinition(const string& name, const Enums::Describer describer, const IDataType* const creationType) : FunctionDefinition(name, describer, creationType)
    { }
}
