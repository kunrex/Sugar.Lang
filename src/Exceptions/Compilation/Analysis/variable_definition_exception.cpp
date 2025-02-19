#include "variable_definition_exception.h"

using namespace std;

using namespace Analysis::Structure;

namespace Exceptions
{
    DuplicateVariableDefinitionException::DuplicateVariableDefinitionException(const unsigned long index, const SourceFile* const source) : LogException("Scope already defines a variable with the same name", index, source)
    { }
}
