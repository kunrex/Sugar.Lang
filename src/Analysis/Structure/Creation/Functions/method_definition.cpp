#include "method_definition.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Creation
{
    MethodDefinition::MethodDefinition(const std::string& name, const Enums::Describer describer, const IDataType* const creationType) : FunctionDefinition(name, describer, creationType)
    { }
}
