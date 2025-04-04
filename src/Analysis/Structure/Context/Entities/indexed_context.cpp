#include "indexed_context.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    IndexedContext::IndexedContext(const IVariable* const variable, const int index) : VariableContext(variable), index(index)
    { }

    uintptr_t IndexedContext::Metadata() const { return index; }
}

