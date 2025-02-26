#include "void_definition.h"

#include <format>

using namespace std;

using namespace Analysis::Structure::Enums;

namespace Analysis::Structure::Creation
{
    VoidDefinition::VoidDefinition(const string& name, const Enums::Describer describer) : FunctionDefinition(name, describer, nullptr)
    { }
}
