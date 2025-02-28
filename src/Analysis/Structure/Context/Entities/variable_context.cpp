#include "variable_context.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    VariableContext::VariableContext(const IVariable* const variable, const bool isLoadInstruction) : ContextNode(variable->CreationType()), isLoadInstruction(isLoadInstruction), variable(variable)
    { }

    bool VariableContext::Readable() const { return variable->Readable(); }
    bool VariableContext::Writable() const { return variable->Writable(); }
}
