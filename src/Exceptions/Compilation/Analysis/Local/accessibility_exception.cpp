#include "accessibility_exception.h"

#include <format>

using namespace std;

using namespace Analysis::Structure;

namespace Exceptions
{
    AccessibilityException::AccessibilityException(const std::string& member, const unsigned long index, const SourceFile* const source) : LogException(std::format("Member: `{}` is not public", member), index, source)
    { }
}
