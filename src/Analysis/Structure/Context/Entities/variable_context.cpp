#include "variable_context.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    VariableContext::VariableContext(const IVariable* const variable) : ContextNode(variable->CreationType()), variable(variable)
    { }

    bool VariableContext::Readable() const { return variable->Readable(); }
    bool VariableContext::Writable() const { return variable->Writable(); }

    uintptr_t VariableContext::Metadata() const { return reinterpret_cast<uintptr_t>(variable); }
    std::string VariableContext::CILData() const { return ""; }
}
