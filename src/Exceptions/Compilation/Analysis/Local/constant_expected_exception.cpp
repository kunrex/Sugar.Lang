#include "constant_expected_exception.h"

using namespace Analysis::Structure;

namespace Exceptions
{
    ConstantNotFoundException::ConstantNotFoundException(const unsigned long index, const SourceFile* const source) : LogException("Expected constant value", index, source)
    { }
}
