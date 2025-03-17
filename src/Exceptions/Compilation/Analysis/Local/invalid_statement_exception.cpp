#include "invalid_statement_exception.h"

using namespace Analysis::Structure;

namespace Exceptions
{
    InvalidStatementException::InvalidStatementException(const unsigned long index, const SourceFile* const source) : LogException("Only assignment ", index, source)
    { }
}

