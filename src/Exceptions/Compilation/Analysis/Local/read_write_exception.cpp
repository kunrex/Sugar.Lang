#include "read_write_exception.h"

using namespace Analysis::Structure;

namespace Exceptions
{
    ReadException::ReadException(const unsigned long index, const SourceFile* const source) : LogException("Cannot read this value", index, source)
    { }

    WriteException::WriteException(const unsigned long index, const SourceFile* const source) : LogException("Cannot write to this value", index, source)
    { }
}
