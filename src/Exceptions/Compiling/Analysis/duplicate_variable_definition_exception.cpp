#include "duplicate_variable_definition_exception.h"

#include <format>

using namespace std;

using namespace Analysis::Structure;

namespace Exceptions
{
    InvalidVariableException::InvalidVariableException(const string& name, const unsigned long index, const SourceFile* source) : LogException(std::format("Scope already defines variable {}", name), index, source)
    { }
}
