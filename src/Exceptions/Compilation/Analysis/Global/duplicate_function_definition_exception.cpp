#include "duplicate_function_definition_exception.h"

using namespace Analysis::Structure;

namespace Exceptions
{
    DuplicateFunctionDefinition::DuplicateFunctionDefinition(const unsigned long index, const SourceFile* const source) : LogException("Scopes already defines a function with the same signature.", index, source)
    { }
}

