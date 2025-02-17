#include "invalid_variable_declaration_exception.h"

#include <format>

using namespace std;

using namespace Analysis::Structure;

namespace Exceptions
{
    InvalidVariableException::InvalidVariableException(const string& name, const unsigned long index, const SourceFile* source) : LogException(std::format("Invalid type for variable: {}", name), index, source)
    { }
}
