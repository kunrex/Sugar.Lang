#include "static_binding_exception.h"

using namespace std;

using namespace Analysis::Structure;

namespace Exceptions
{
    StaticBindingException::StaticBindingException(const unsigned long index, const SourceFile* const source) : LogException("Static structures can only define static members", index, source)
    { }
}