#include "variable_context.h"

using namespace Analysis::Structure::Creation;

namespace Analysis::Structure::Context
{
    VariableContext::VariableContext(const Variable* variable) : ContextNode(variable->CreationType()), variable(variable)
    { }
}
