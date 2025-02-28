#include "indexed_context.h"

using namespace Analysis::Structure::Core::Interfaces;

namespace Analysis::Structure::Context
{
    IndexedContext::IndexedContext(const IVariable* variable, const bool isLoadInstruction, const int index) : VariableContext(variable, isLoadInstruction), index(index)
    { }

    int IndexedContext::Index() const { return index; }
}

