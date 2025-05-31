#include "invalid_statement_exception.h"

using namespace Analysis::Structure;

namespace Exceptions
{
    InvalidStatementException::InvalidStatementException(const unsigned long index, const SourceFile* const source) : LogException("Only initialisation, expression and function call can be a valid statement", index, source)
    { }
}

