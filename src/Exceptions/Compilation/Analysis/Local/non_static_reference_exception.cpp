#include "non_static_reference_exception.h"

#include <format>

using namespace std;

using namespace Analysis::Structure;

namespace Exceptions
{
    NonStaticReferenceException::NonStaticReferenceException(const string& referenced, const unsigned long index, const SourceFile* const source) : LogException(std::format("Trying to reference non static: `{}` from a static scope", referenced), index, source)
    { }
}
