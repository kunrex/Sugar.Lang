#include "variable_context.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    VariableContext::VariableContext(const IVariable* const variable) : ContextNode(variable->CreationType()), variable(variable)
    { }

    bool VariableContext::Readable() const { return variable->Readable(); }
    bool VariableContext::Writable() const { return variable->Writable(); }

    std::string VariableContext::CILData() const { return ""; }

    const IVariable* VariableContext::Variable() const { return variable; }
}
