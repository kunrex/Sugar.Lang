#include "void_definition.h"

#include "../../Wrappers/Reference/void.h"

using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Creation
{
    VoidDefinition::VoidDefinition(const std::string& name, const Enums::Describer describer) : FunctionDefinition(name, describer, Void::Instance())
    { }
}
