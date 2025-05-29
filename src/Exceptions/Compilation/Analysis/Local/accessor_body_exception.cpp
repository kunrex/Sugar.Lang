#include "accessor_body_exception.h"

using namespace Analysis::Structure;

namespace Exceptions
{
    AccessorBodyException::AccessorBodyException(const unsigned long index, const SourceFile* const source) : LogException("Accessors must define a body", index, source)
    { }
}
