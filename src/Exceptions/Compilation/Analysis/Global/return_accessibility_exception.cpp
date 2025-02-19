#include "return_accessibility_exception.h"

using namespace std;

using namespace Analysis::Structure;

namespace Exceptions
{
    ReturnAccessibilityException::ReturnAccessibilityException(const unsigned long index, const SourceFile* const source) : LogException("Return type is less accessible than member.", index, source)
    { }
}
