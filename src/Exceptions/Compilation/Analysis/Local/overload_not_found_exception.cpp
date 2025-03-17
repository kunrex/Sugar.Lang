#include "overload_not_found_exception.h"

#include <format>

using namespace Tokens::Enums;

using namespace Analysis::Structure;

namespace Exceptions
{
    OverloadNotFoundException::OverloadNotFoundException(const SyntaxKind kind, const unsigned long index, const SourceFile* const source) : LogException(std::format("No overload found for: {}", ToString(kind)), index, source)
    { }
}
