#include "invalid_global_statement_exception.h"

using namespace Analysis::Structure;

namespace Exceptions
{
    InvalidGlobalStatementException::InvalidGlobalStatementException(const unsigned long index, const SourceFile* const source) : LogException("Global scopes can contain only variable, property and function definitions.", index, source)
    { }
}

