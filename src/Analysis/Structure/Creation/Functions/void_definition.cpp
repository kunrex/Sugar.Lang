#include "void_definition.h"

#include <format>

#include "../../Wrappers/Reference/void.h"

using namespace std;

using namespace Analysis::Structure::Enums;
using namespace Analysis::Structure::Wrappers;

namespace Analysis::Structure::Creation
{
    VoidDefinition::VoidDefinition(const string& name, const Enums::Describer describer) : FunctionDefinition(name, describer, &Void::Instance())
    { }
}
