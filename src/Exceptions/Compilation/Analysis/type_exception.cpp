#include "type_exception.h"

using namespace std;

using namespace Analysis::Structure;

namespace Exceptions
{
    TypeNotFoundException::TypeNotFoundException(const unsigned long index, const SourceFile* const source) : LogException("Failed to reference type", index, source)
    { }

    InvalidTypeException::InvalidTypeException(const unsigned long index, const SourceFile* const source) : LogException("Type is not applicable for this member", index, source)
    { }
}

