#include "variable_context.h"

using namespace Analysis::Structure::Core;

namespace Analysis::Structure::Context
{
    VariableContext::VariableContext(const Characteristic* characteristic) : ContextNode(characteristic->CreationType(), characteristic->CheckDescriber(Enums::Describer::Static)), characteristic(characteristic)
    { }
}
