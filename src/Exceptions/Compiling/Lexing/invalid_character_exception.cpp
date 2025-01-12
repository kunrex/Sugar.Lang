#include "invalid_character_exception.h"

#include <format>

using namespace Analysis::Structure;

namespace Exceptions
{
    InvalidCharacterException::InvalidCharacterException(const char c, const unsigned long index, const SourceFile* source) : LogException(std::format("Invalid character: {}", c), index, source)
    { }
}
