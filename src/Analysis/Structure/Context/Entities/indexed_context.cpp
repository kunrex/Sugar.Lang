#include "indexed_context.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    IndexedContext::IndexedContext(const IVariable* const variable, const int index) : VariableContext(variable), index(index)
    { }

    int IndexedContext::Index() const { return index; }
}

