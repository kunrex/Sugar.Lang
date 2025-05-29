#include "return_value_exception.h"

using namespace Tokens::Enums;

using namespace Analysis::Structure;

namespace Exceptions
{
    ReturnValueException::ReturnValueException(const unsigned long index, const SourceFile* const source) : LogException("Not all paths return a value", index, source)
    { }
}
